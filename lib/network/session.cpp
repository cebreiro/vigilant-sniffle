#include "session.h"

#include "lib/common/execution/future_await.h"
#include "lib/network/socket.h"
#include "lib/network/session_handler.h"
#include "lib/network/decoder.h"
#include "lib/network/encoder.h"

namespace cebreiro::network
{
	Session::Session(Id_t id, 
		std::shared_ptr<Socket> socket,
		std::unique_ptr<Decoder> decoder,
		std::unique_ptr<Encoder> encoder,
		SessionHandler& handler)
		: _id(id)
		, _socket(std::move(socket))
		, _decoder(std::move(decoder))
		, _encoder(std::move(encoder))
		, _handler(handler)
		, _receiveBuffer(RECEIVE_BUFFER_MIN_SIZE)
		, _strand(ThreadPool::GetInstance().MakeStrand())
	{
		assert(_decoder);
		assert(_encoder);
	}

	Session::~Session()
	{
	}

	void Session::StartReceive()
	{
		if (_shutdown)
		{
			return;
		}

		bool expected = false;
		if (_receiveStarted.compare_exchange_strong(expected, true))
		{
			ReceiveOperation().ContinuationWith([self = shared_from_this()](Future<void>& op)
			{
				try
				{
					op.Get();
				}
				catch (const std::exception& e)
				{
					self->_handler.UnhandledException(*self, e);
					self->_shutdown.store(true);
				}

				self->_receiveStarted.store(false);

			}, Executor::GetThreadPool());
		}
	}

	void Session::Close()
	{
		_shutdown = true;
		_socket->Close();
	}

	void Session::Send(Buffer buffer, bool encode)
	{
		if (_shutdown)
		{
			return;
		}

		Post([self = shared_from_this(), buffer = std::move(buffer), encode]() mutable
			{
				if (encode)
				{
					self->_encoder->Encode(std::span(buffer.Data(), buffer.Size()));
				}

				self->StartSend(std::move(buffer));
			}, _strand);
	}

	auto Session::Id() const -> Id_t
	{
		return _id;
	}

	auto Session::LocalAddress() const -> const std::string&
	{
		return _socket->LocalAddress();
	}

	auto Session::LocalPort() const -> uint16_t
	{
		return _socket->LocalPort();
	}

	auto Session::RemoteAddress() const -> const std::string&
	{
		return _socket->RemoteAddress();
	}

	auto Session::RemotePort() const -> uint16_t
	{
		return _socket->RemotePort();
	}

	void Session::StartSend(Buffer buffer)
	{
		bool launchOperation = false;
		{
			std::lock_guard lock(_sendMutex);
			_sendBuffers.push(std::move(buffer));

			if (!_sendLock)
			{
				_sendLock = launchOperation = true;
			}
		}

		if (launchOperation)
		{
			(void)SendOperation().ContinuationWith([self = shared_from_this()](Future<void>& op)
				{
					try
					{
						op.Get();
					}
					catch (const std::exception& e)
					{
						self->_handler.UnhandledException(*self, e);
						self->_shutdown.store(true);
					}
				}, Executor::GetThreadPool());
		}
	}

	auto Session::SendOperation() -> Future<void>
	{
		std::shared_ptr<Session> self = shared_from_this();

		while (!_shutdown)
		{
			Buffer buffer;
			{
				std::lock_guard lock(_sendMutex);
				if (_sendBuffers.empty())
				{
					_sendLock = false;
					co_return;
				}

				buffer = std::move(_sendBuffers.front());
				_sendBuffers.pop();
			}

			std::span span(buffer.Data(), buffer.Size());
			const auto& [error, sendSize] = co_await _socket->WriteAsync(span);
			if (!error)
			{
				assert(buffer.Size() == sendSize);
				_handler.OnSend(*self, buffer);
			}
			else
			{
				_handler.OnError(*self, error);
				co_return;
			}
		}
	}

	auto Session::ReceiveOperation() -> Future<void>
	{
		std::shared_ptr<Session> self = shared_from_this();

		while (!_shutdown)
		{
			std::span<char> buffer = [](ReceiveBuffer& receiveBuffer)
			{
				char* buffer = receiveBuffer.Data() + receiveBuffer.ReceiveSize();
				size_t size = receiveBuffer.Size() - receiveBuffer.ReceiveSize();

				return std::span(buffer, size);
			}(_receiveBuffer);

			const auto&[error, readSize] =  co_await _socket->ReadAsync(buffer);
			if (!error)
			{
				_receiveBuffer.AddReceiveSize(readSize);

				while (true)
				{
					auto result = _decoder->GetPacketSize(std::span(_receiveBuffer.Data(), _receiveBuffer.ReceiveSize()));
					if (result.has_value())
					{
						size_t packetSize = result.value();
						assert(packetSize != 0);

						if (packetSize >= RECEIVE_BUFFER_MAX_SIZE)
						{
							_handler.OnError(*self, _asio::error::no_buffer_space);
							_shutdown.store(true);

							co_return;
						}

						if (packetSize > _receiveBuffer.GetBufferMaxSize())
						{
							_receiveBuffer.Resize(packetSize);
							break;
						}

						if (packetSize <= _receiveBuffer.ReceiveSize())
						{
							Buffer received = _receiveBuffer.SliceFront(packetSize);
							if (!_receiveBuffer.IsValid())
							{
								_receiveBuffer.Reset();
							}

							_decoder->Decode(std::span(received.Data(), received.Size()));
							_handler.OnReceive(*self, received);
						}
					}
					else
					{
						Decoder::DecodeError decodeError = result.error();
						if (decodeError == Decoder::DecodeError::ErrorShortLength)
						{
							break;
						}
						else if (decodeError == Decoder::DecodeError::ErrorInvalidHead)
						{
							_handler.OnError(*self, _asio::error::invalid_argument);
							_shutdown.store(true);

							co_return;
						}
						else
						{
							assert(false);
						}
					}
				}
			}
			else
			{
				_handler.OnError(*self, error);
				_shutdown.store(true);

				co_return;
			}
		}
	}
}

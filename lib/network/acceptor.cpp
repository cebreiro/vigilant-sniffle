#include "acceptor.h"

#include "lib/common/execution/promise.h"
#include "lib/common/execution/future_await.h"
#include "lib/network/accept_handler.h"
#include "lib/network/network_executor.h"

namespace cebreiro::network
{
	Acceptor::Acceptor(NetworkExecutor& executor, uint16_t port, AcceptHandler& handler)
		: _executor(executor)
		, _rawAcceptor(_executor.GetIoContext(), endpoint_t(_asio::ip::tcp::v4(), port), false)
		, _handler(handler)
	{
		assert(_rawAcceptor.is_open());
	}

	Acceptor::~Acceptor()
	{
	}

	void Acceptor::StartAccept()
	{
		(void)Run().ContinuationWith([self = shared_from_this()](Future<void>& op)
			{
				try
				{
					op.Get();
				}
				catch(const std::exception& e)
				{
					self->_handler.UnhandledException(*self, e);
				}
			}, _executor);
	}

	void Acceptor::Close()
	{
		_shutdown.store(true);
		_rawAcceptor.cancel();
	}

	auto Acceptor::Run() -> Future<void>
	{
		std::shared_ptr<Acceptor> self = shared_from_this();

		while (!_shutdown)
		{
			Expected<std::shared_ptr<Socket>> expected = co_await AcceptAsync();
			if (expected.has_value())
			{
				_handler.OnAccept(*self, expected.value());
			}
			else
			{
				_handler.OnError(*self, expected.error());
			}
		}
	}

	auto Acceptor::AcceptAsync() -> Future<Expected<std::shared_ptr<Socket>>>
	{
		Promise<Expected<std::shared_ptr<Socket>>> promise;
		Future<Expected<std::shared_ptr<Socket>>> future = promise.GetFuture();

		_rawAcceptor.async_accept([this, p = std::move(promise)](const error_t& error, raw_socket_t socket) mutable
			{
				if (error)
				{
					p.Set(std::unexpected(error));
				}
				else
				{
					p.Set(std::make_shared<Socket>(std::move(socket)));
				}
			});

		return future;
	}
}

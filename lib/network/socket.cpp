#include "socket.h"

#include "lib/common/execution/promise.h"

namespace cebreiro::network
{
	Socket::Socket(raw_socket_t rawSocket)
		: _rawSocket(std::move(rawSocket))
		, _strand(boost::asio::make_strand(_rawSocket.get_executor()))
		, _localAddress(_rawSocket.local_endpoint().address().to_string())
		, _localPort(_rawSocket.local_endpoint().port())
		, _remoteAddress(_rawSocket.remote_endpoint().address().to_string())
		, _remotePort(_rawSocket.remote_endpoint().port())
	{
	}

	Socket::~Socket()
	{
	}

	auto Socket::WriteAsync(std::span<char> buffer) -> Future<std::pair<error_t, size_t>>
	{
		Promise<std::pair<error_t, size_t>> promise;
		Future<std::pair<error_t, size_t>> future = promise.GetFuture();

		post(_strand, [self = shared_from_this(), buffer, p = std::move(promise)]() mutable
			{
				async_write(
					self->_rawSocket,
					_asio::buffer(buffer),
					bind_executor(self->_strand, [self, p = std::move(p)](const error_t& error, size_t bytes) mutable
						{
							p.Set({ error, bytes });
						}));
			});

		return future;
	}

	auto Socket::ReadAsync(std::span<char> buffer) -> Future<std::pair<error_t, size_t>>
	{
		Promise<std::pair<error_t, size_t>> promise;
		Future<std::pair<error_t, size_t>> future = promise.GetFuture();

		post(_strand, [self = shared_from_this(), buffer, p = std::move(promise)]() mutable
			{
				self->_rawSocket.async_read_some(
					_asio::buffer(buffer),
					bind_executor(self->_strand, [self, p = std::move(p)](const error_t& error, size_t bytes) mutable
						{
							p.Set({ error, bytes });
						}));
			});

		return future;
	}

	void Socket::Close()
	{
		post(_strand, [self = shared_from_this()]()
			{
				if (self->_rawSocket.is_open())
				{
					self->_rawSocket.close();
				}
			});
	}

	auto Socket::LocalAddress() const -> const std::string&
	{
		return _localAddress;
	}

	auto Socket::LocalPort() const -> uint16_t
	{
		return _localPort;
	}

	auto Socket::RemoteAddress() const -> const std::string&
	{
		return _remoteAddress;
	}

	auto Socket::RemotePort() const -> uint16_t
	{
		return _remotePort;
	}
}

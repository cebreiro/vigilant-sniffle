#include "connector.h"

#include <format>
#include <iostream>

#include "lib/common/stacktrace_exception.h"
#include "lib/common/execution/promise.h"
#include "lib/common/execution/future_await.h"

namespace cebreiro::network
{
	Connector::Connector(io_context_t& ioContext, uint64_t reconnectMilliseconds)
		: _ioContext(ioContext)
		, _reconnectMilliseconds(reconnectMilliseconds)
	{
	}

	auto Connector::ConnectAsync(std::string address, uint16_t port) -> Future<std::shared_ptr<Socket>>
	{
		std::shared_ptr<Connector> self = shared_from_this();

		raw_socket_t socket(_ioContext);
		endpoint_t endpoint(_asio::ip::make_address(address), port);

		do
		{
			Promise<error_t> promise;
			Future<error_t> future = promise.GetFuture();

			socket.async_connect(endpoint, [promise = std::move(promise)](const error_t& error) mutable
				{
					promise.Set(error);
				});

			const error_t& error = co_await future;
			if (error)
			{
				std::cout << std::format("connect error: {}\n", error.message());
				co_await Delay(self->_reconnectMilliseconds);
			}
			else
			{
				co_return std::make_shared<Socket>(std::move(socket));
			}

		} while (!_shutdown);

		throw StacktraceException("connect_async is canceled");
	}

	void Connector::Close()
	{
		_shutdown = true;
	}
}

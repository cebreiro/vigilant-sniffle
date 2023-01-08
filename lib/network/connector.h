#pragma once
#include <cstdint>
#include <atomic>
#include <string>
#include <memory>

#include "lib/common/execution/future.h"
#include "lib/network/socket.h"

namespace cebreiro::network
{
	class Connector : public std::enable_shared_from_this<Connector>
	{
	public:
		Connector(io_context_t& ioContext, uint64_t reconnectMilliseconds);

		auto ConnectAsync(std::string address, uint16_t port) -> Future<std::shared_ptr<Socket>>;
		void Close();

	private:
		io_context_t& _ioContext;
		uint64_t _reconnectMilliseconds;
		std::atomic<bool> _shutdown = false;
	};
}
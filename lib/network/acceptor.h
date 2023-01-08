#pragma once
#include <atomic>
#include "lib/common/execution/future.h"
#include "lib/network/socket.h"

namespace cebreiro::network
{
	class NetworkExecutor;
	class AcceptHandler;

	class Acceptor : public std::enable_shared_from_this<Acceptor>
	{
	public:
		Acceptor(NetworkExecutor& executor, uint16_t port, AcceptHandler& handler);
		~Acceptor();

		void StartAccept();
		void Close();

	private:
		auto Run() -> Future<void>;
		auto AcceptAsync() -> Future<Expected<std::shared_ptr<Socket>>>;

	private:
		NetworkExecutor& _executor;
		raw_acceptor_t _rawAcceptor;
		AcceptHandler& _handler;

		std::atomic<bool> _start = false;
		std::atomic<bool> _shutdown = false;
	};
}
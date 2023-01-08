#pragma once
#include <queue>
#include <mutex>
#include <tbb/concurrent_vector.h>

#include "lib/network/acceptor.h"
#include "lib/network/accept_handler.h"
#include "lib/network/session.h"
#include "lib/network/session_handler.h"

class TestServer : public cebreiro::network::Acceptor, public cebreiro::network::AcceptHandler
{
	struct Session : cebreiro::network::Session, cebreiro::network::SessionHandler
	{
		Session(Id_t id, std::shared_ptr<cebreiro::network::Socket> socket);

		void OnSend(cebreiro::network::Session& session, cebreiro::network::Buffer& buffer) override;
		void OnReceive(cebreiro::network::Session& session, cebreiro::network::Buffer& buffer) override;
		void OnError(cebreiro::network::Session& session, const cebreiro::network::error_t& error) override;
		void UnhandledException(cebreiro::network::Session& session, const std::exception& exception) override;

		mutable std::mutex _sendMutex;
		bool _sending = false;
		std::queue<cebreiro::network::Buffer> _sendBuffers;
	};

public:
	TestServer(cebreiro::network::NetworkExecutor& executor, uint16_t port);

	void OnAccept(Acceptor& acceptor, std::shared_ptr<cebreiro::network::Socket> socket) override;
	void OnError(Acceptor& acceptor, const cebreiro::network::error_t& error) override;
	void UnhandledException(Acceptor& acceptor, const std::exception& exception) override;

	tbb::concurrent_vector<std::shared_ptr<Session>> _sessions;
};
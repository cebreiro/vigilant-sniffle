#pragma once
#include <vector>
#include <mutex>

#include "lib/network/session.h"
#include "lib/network/session_handler.h"

struct TestClient : cebreiro::network::Session, cebreiro::network::SessionHandler
{
	TestClient(Id_t id, std::shared_ptr<cebreiro::network::Socket> socket, std::vector<std::vector<char>> sendBytes);

	void Start();
	bool IsDone() const;

	void OnSend(Session& session, cebreiro::network::Buffer& buffer) override;
	void OnReceive(Session& session, cebreiro::network::Buffer& receiveBuffer) override;
	void OnError(Session& session, const cebreiro::network::error_t& error) override;
	void UnhandledException(Session& session, const std::exception& exception) override;

	std::vector<std::vector<char>> _sendBytes;
	size_t _sendBytesSize = 0;

	mutable std::mutex _sendMutex;
	std::vector<cebreiro::network::Buffer> _sends;

	mutable std::mutex _receiveMutex;
	std::vector<cebreiro::network::Buffer> _receives;
};
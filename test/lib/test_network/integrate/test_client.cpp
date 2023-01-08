#include "test_client.h"

#include <cassert>
#include <format>
#include <iostream>

#include "test_decoder_encoder.h"
#include "lib/network/connector.h"

TestClient::TestClient(Id_t id, std::shared_ptr<cebreiro::network::Socket> socket, std::vector<std::vector<char>> sendBytes)
	: Session(id, std::move(socket), std::make_unique<TestDecoder>(), std::make_unique<TestEncoder>(), *this)
	, _sendBytes(std::move(sendBytes))
{
	for (const std::vector<char>& buffer : _sendBytes)
	{
		_sendBytesSize += buffer.size();
	}
}

void TestClient::Start()
{
	StartReceive();

	for (const std::vector<char>& buffer : _sendBytes)
	{
		auto temp = std::make_shared<char[]>(buffer.size());
		std::copy_n(buffer.begin(), buffer.size(), temp.get());

		Send(cebreiro::network::Buffer(std::move(temp), 0, buffer.size()));
	}
}

bool TestClient::IsDone() const
{
	size_t size = 0;

	{
		std::lock_guard lock(_receiveMutex);
		for (const cebreiro::network::Buffer& buffer : _receives)
		{
			size += buffer.Size();
		}
	}

	return size == _sendBytesSize;
}

void TestClient::OnSend([[maybe_unused]] Session& session, cebreiro::network::Buffer& buffer)
{
	assert(this == &session);

	std::lock_guard lock(_sendMutex);
	_sends.push_back(std::move(buffer));
}

void TestClient::OnReceive([[maybe_unused]] Session& session, cebreiro::network::Buffer& receiveBuffer)
{
	assert(this == &session);

	std::lock_guard lock(_receiveMutex);
	_receives.push_back(std::move(receiveBuffer));
}

void TestClient::OnError([[maybe_unused]] Session& session, const cebreiro::network::error_t& error)
{
	assert(this == &session);

	std::cout << std::format("client error: {}\n", error.message());
	assert(false);
}

void TestClient::UnhandledException([[maybe_unused]] Session& session, const std::exception& exception)
{
	assert(this == &session);

	std::cout << std::format("client exception: {}\n", exception.what());
	assert(false);
}

#include "test_server.h"

#include <cassert>
#include <format>
#include <iostream>

#include "test_decoder_encoder.h"

TestServer::Session::Session(Id_t id, std::shared_ptr<cebreiro::network::Socket> socket)
	: cebreiro::network::Session(id, std::move(socket), std::make_unique<TestDecoder>(), std::make_unique<TestEncoder>(), *this)
{
}

void TestServer::Session::OnSend([[maybe_unused]] cebreiro::network::Session& session, [[maybe_unused]] cebreiro::network::Buffer& buffer)
{
	assert(this == &session);

	cebreiro::network::Buffer sendBuffer;
	{
		std::lock_guard lock(_sendMutex);
		if (_sendBuffers.empty())
		{
			_sending = false;
			return;
		}
		else
		{
			sendBuffer = std::move(_sendBuffers.front());
			_sendBuffers.pop();
		}
	}

	if (sendBuffer.IsValid())
	{
		session.Send(std::move(sendBuffer));
	}
}

void TestServer::Session::OnReceive([[maybe_unused]] cebreiro::network::Session& session, cebreiro::network::Buffer& buffer)
{
	assert(this == &session);

	{
		std::lock_guard lock(_sendMutex);
		if (!_sending)
		{
			_sending = true;
			session.Send(std::move(buffer));
		}
		else
		{
			_sendBuffers.push(std::move(buffer));
		}
	}
}

void TestServer::Session::OnError([[maybe_unused]] cebreiro::network::Session& session, const cebreiro::network::error_t& error)
{
	assert(this == &session);

	std::cout << std::format("server session error: {}\n", error.message());
	assert(false);
}

void TestServer::Session::UnhandledException([[maybe_unused]] cebreiro::network::Session& session, const std::exception& exception)
{
	assert(this == &session);

	std::cout << std::format("server session exception: {}\n", exception.what());
	assert(false);
}

TestServer::TestServer(cebreiro::network::NetworkExecutor& executor, uint16_t port)
	: Acceptor(executor, port, *this)
{
}

void TestServer::OnAccept([[maybe_unused]] Acceptor& acceptor, std::shared_ptr<cebreiro::network::Socket> socket)
{
	assert(this == &acceptor);

	_sessions.emplace_back(std::make_shared<Session>(Session::Id_t(0), std::move(socket)))
		->get()->StartReceive();
}

void TestServer::OnError([[maybe_unused]] Acceptor& acceptor, const cebreiro::network::error_t& error)
{
	assert(this == &acceptor);

	std::cout << std::format("server error: {}\n", error.message());
	assert(false);
}

void TestServer::UnhandledException([[maybe_unused]] Acceptor& acceptor, const std::exception& exception)
{
	assert(this == &acceptor);

	std::cout << std::format("server exception: {}\n", exception.what());
	assert(false);
}

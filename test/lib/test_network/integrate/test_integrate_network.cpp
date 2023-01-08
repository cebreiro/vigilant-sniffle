#include "gtest/gtest.h"

#include <thread>
#include <vector>
#include <format>
#include <random>
#include <execution>
#include <ranges>
#include <algorithm>
#include <tbb/concurrent_queue.h>

#include "test_client.h"
#include "test_server.h"
#include "lib/common/stacktrace_exception.h"
#include "lib/common/execution/future.h"
#include "lib/common/execution/future_await.h"
#include "lib/network/acceptor.h"
#include "lib/network/accept_handler.h"
#include "lib/network/buffer.h"
#include "lib/network/connector.h"
#include "lib/network/network_executor.h"
#include "lib/network/session.h"
#include "lib/network/socket.h"

namespace _asio = cebreiro::network::_asio;

using cebreiro::Future;
using cebreiro::network::io_context_t;
using cebreiro::network::Connector;
using cebreiro::network::Session;
using cebreiro::network::Socket;
using cebreiro::network::Buffer;


auto GenerateRandomBytes(size_t count) -> std::vector<char>
{
	static const char alphanum[] =
		"0123456789"
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"abcdefghijklmnopqrstuvwxyz";

	std::vector<char> temp;
	temp.reserve(count);

	for (int i = 0; i < count; ++i) {
		temp.push_back(alphanum[rand() % (sizeof(alphanum) - 1)]);
	}

	return temp;
}

auto GenerateRandomBytesArray(size_t arrayLength) -> std::vector<std::vector<char>>
{
	std::mt19937 mt(std::random_device{}());
	std::uniform_int_distribution<size_t> dist(1024, 4096);

	std::vector<std::vector<char>> buffers(arrayLength);
	for (size_t i = 0; i < arrayLength; ++i)
	{
		buffers[i] = GenerateRandomBytes(dist(mt));
	}

	return buffers;
}

constexpr uint16_t PORT = 7878;
constexpr size_t TEST_SESSION_COUNT = 50;
constexpr size_t ECHO_COUNT = 100;

auto ConnectClients(Connector& connector, uint16_t port) -> Future<std::vector<std::shared_ptr<TestClient>>>
{
	std::vector<std::shared_ptr<TestClient>> clients;

	for (size_t i = 0; i < TEST_SESSION_COUNT; ++i)
	{
		std::shared_ptr<Socket> socket = co_await connector.ConnectAsync("127.0.0.1", port);
		clients.emplace_back(std::make_shared<TestClient>(Session::Id_t(i), std::move(socket), GenerateRandomBytesArray(ECHO_COUNT)));
	}

	co_return clients;
}

auto ToVector(const std::vector<Buffer>& buffers) -> std::vector<char>
{
	std::vector<char> result;

	for (const Buffer& buffer : buffers)
	{
		std::copy_n(buffer.Data(), buffer.Size(), std::back_inserter(result));
	}

	return result;
}

TEST(IntegrateNetworkTest, Echo)
{
	auto executor = std::make_shared<cebreiro::network::NetworkExecutor>();

	auto server = std::make_shared<TestServer>(*executor, PORT);
	server->StartAccept();

	constexpr uint64_t reconnectMilliseconds = 5000;
	std::shared_ptr<Connector> connector = std::make_shared<Connector>(executor->GetIoContext(), reconnectMilliseconds);
	std::vector<std::shared_ptr<TestClient>> clients = ConnectClients(*connector, PORT).Get();

	std::for_each(std::execution::par, clients.begin(), clients.end(), [](const std::shared_ptr<TestClient>& client)
		{
			client->Start();
		});

	for (const std::shared_ptr<TestClient>& client : clients)
	{
		while (!client->IsDone())
		{
			std::this_thread::sleep_for(std::chrono::seconds(1));
		}
		
		std::vector<char> sends = ToVector(client->_sends);
		std::vector<char> receives = ToVector(client->_receives);

		ASSERT_EQ(sends.size(), receives.size());

		for (size_t i = 0; i < sends.size(); ++i)
		{
			ASSERT_EQ(sends[i], receives[i]);
		}
	}

	executor->Stop();
};
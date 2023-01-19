#pragma once
#include "lib/network/accept_handler.h"
#include "lib/network/session.h"
#include "lib/network/session_handler.h"

namespace cebreiro
{
	class IServiceLocator;
}

namespace cebreiro::network
{
	class NetworkExecutor;
	class Acceptor;
}

namespace cebreiro::zone
{
	class Zone;
	struct ZoneSessionContext;
}

namespace cebreiro::zone
{
	class ZoneServer : public network::AcceptHandler, public network::SessionHandler
	{
	public:
		ZoneServer(const IServiceLocator& serviceLocator, network::NetworkExecutor& networkExecutor,
			uint16_t port, std::shared_ptr<Zone> zone);

		void Start();
		void Stop();

	private:
		void OnAccept(network::Acceptor& acceptor, std::shared_ptr<network::Socket> socket) override;
		void OnError(network::Acceptor& acceptor, const network::error_t& error) override;
		void UnhandledException(network::Acceptor& acceptor, const std::exception& exception) override;

	private:
		void OnSend(network::Session& session, network::Buffer& buffer) override;
		void OnReceive(network::Session& session, network::Buffer& buffer) override;
		void OnError(network::Session& session, const network::error_t& error) override;
		void UnhandledException(network::Session& session, const std::exception& exception) override;

	private:
		void HandleMessageException(const ZoneSessionContext& context, const std::exception& exception);

		void RemoveSession(network::Session& session);

	private:
		const IServiceLocator& _locator;
		network::NetworkExecutor& _networkExecutor;
		std::shared_ptr<network::Acceptor> _acceptor;

		tbb::concurrent_hash_map<network::Session::Id_t, std::shared_ptr<ZoneSessionContext>> _sessions;

		std::mutex _sessionsForIterationMutex;
		std::vector<std::shared_ptr<ZoneSessionContext>> _sessionsForIteration;

		std::atomic<bool> _shutdown = false;
		std::atomic<uint64_t> _nextSessionId = 1;

		std::shared_ptr<Zone> _zone;
	};
}
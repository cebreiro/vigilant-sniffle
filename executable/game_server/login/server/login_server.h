#pragma once
#include "lib/network/accept_handler.h"
#include "lib/network/session.h"
#include "lib/network/session_handler.h"
#include "login/server/login_session_context.h"

namespace cebreiro
{
	class IServiceLocator;
}

namespace cebreiro::network
{
	class NetworkExecutor;
	class Acceptor;
}

namespace cebreiro::login
{
	struct LoginSessionContext;

	class LoginServer : public network::AcceptHandler, public network::SessionHandler
	{
	public:
		LoginServer(const IServiceLocator& serviceLocator, network::NetworkExecutor& networkExecutor);

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
		void HandleMessageException(const LoginSessionContext& context, const std::exception& exception);

		void RemoveSession(const network::Session& session);

	private:
		const IServiceLocator& _locator;
		network::NetworkExecutor& _networkExecutor;
		std::shared_ptr<network::Acceptor> _acceptor;
		tbb::concurrent_hash_map<network::Session::Id_t, std::shared_ptr<LoginSessionContext>> _sessions;

		std::mutex _sessionsForIterationMutex;
		std::vector<std::shared_ptr<LoginSessionContext>> _sessionsForIteration;

		std::atomic<bool> _shutdown = false;
		std::atomic<uint64_t> _nextSessionId = 1;
	};
}

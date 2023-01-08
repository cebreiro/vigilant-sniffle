#pragma once
#include "config/server_config.h"
#include "service/service_locator.h"

namespace cebreiro
{
	class ThreadPool;
}

namespace cebreiro::network
{
	class NetworkExecutor;
}

namespace cebreiro::gamedb
{
	class GameDB;
}

namespace cebreiro::login
{
	class LoginServer;
}

namespace cebreiro::gateway
{
	class GatewayServer;
}

namespace cebreiro
{
	class GameServer
	{
	public:
		~GameServer();

		auto Run(const std::span<char*>& args) -> int;

	private:
		void InitializeExecutors();
		void InitializeGameData();
		void InitializeServices();
		void InitializeServers();
		void Finalize();

	private:
		ServerConfig _config;

		std::shared_ptr<ILogService> _logService;

		std::shared_ptr<network::NetworkExecutor> _networkExecutor;
		std::shared_ptr<ThreadPool> _dbExecutor;
		;
		std::shared_ptr<gamedata::GameDataSource> _gameDataSource;
		std::shared_ptr<gamedb::GameDB> _gameDB;

		std::shared_ptr<ILoginService> _loginService;
		std::vector<std::shared_ptr<IWorldService>> _worldServices;
		ServiceLocator _serviceLocator;

		std::shared_ptr<login::LoginServer> _loginServer;
		std::shared_ptr<gateway::GatewayServer> _gatewayServer;

		std::vector<std::function<void()>> _finalizers;
	};
}
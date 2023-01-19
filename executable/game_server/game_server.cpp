#include "game_server.h"

#include "gateway/server/gateway_server.h"
#include "lib/common/log/detail/spd_log_service.h"
#include "lib/game_data/game_data_source.h"
#include "lib/odbc/data_source.h"
#include "lib/game_db/game_db.h"
#include "lib/network/network_executor.h"
#include "login/service/login_service.h"
#include "login/server/login_server.h"
#include "world/world_service.h"
#include "zone/game/zone.h"

namespace cebreiro
{
	GameServer::~GameServer()
	{
		Finalize();
	}

	auto GameServer::Run(const std::span<char*>& args) -> int
	{
		try
		{
			_config.InitializeFromJson(fs::path(args[0]).parent_path().string().c_str());

			SpdLogServiceConstructParam param{
				.console = SpdLogServiceConstructParam::Console{
					.async = _config.log.console.async,
					.level = static_cast<LogLevel>(_config.log.console.level),
				},
				.dailyFile = SpdLogServiceConstructParam::DailyFile{
					.path = _config.log.dailyFile.path,
					.level = static_cast<LogLevel>(_config.log.dailyFile.level),
				},
			};

			_logService = std::make_shared<SpdLogService>(param);
			_serviceLocator.SetLogService(_logService.get());

			LOGI(*_logService, "initialize LogService DONE")
		}
		catch (const std::exception& e)
		{
			std::cout << e.what();
			return EXIT_FAILURE;
		}

		try
		{
			InitializeExecutors();
			InitializeGameData();
			InitializeServices();
			InitializeServers();


			while (true)
			{
				std::string str;
				std::getline(std::cin, str);
			}
		}
		catch (const std::exception&)
		{
			return EXIT_FAILURE;
		}

		return EXIT_SUCCESS;
	}

	void GameServer::InitializeExecutors()
	{
		auto initializeNetworkExecutor = [this]()
		{
			_networkExecutor = std::make_shared<network::NetworkExecutor>(_config.executor.networkConcurrency);
			_finalizers.emplace_back([this]()
				{
					_networkExecutor->Stop();
				});

			LOGI(*_logService, "initialize NetworkExecutor DONE")
		};
		initializeNetworkExecutor();

		auto initializeDBExecutor = [this]()
		{
			_dbExecutor = std::make_shared<ThreadPool>(_config.executor.dbConcurrency);
			_finalizers.emplace_back([this]()
				{
					_dbExecutor->Stop();
				});

			LOGI(*_logService, "initialize NetworkExecutor DONE")
		};
		initializeDBExecutor();
	}

	void GameServer::InitializeGameData()
	{
		auto initializeGameData = [this]()
		{
			_gameDataSource = std::make_shared<gamedata::GameDataSource>(_config.gameData.path);
			_gameDataSource->Reload();

			_serviceLocator.SetGameDataSource(_gameDataSource.get());

			LOGI(*_logService, "initialize GameDataSource DONE")
		};
		initializeGameData();

		auto initializeGameDB = [this]()
		{
			auto dataSource = std::make_shared<odbc::DataSource>(
				_config.gameDB.odbcDSN, _config.gameDB.odbcUser, _config.gameDB.odbcPassword);

			_gameDB = std::make_shared<gamedb::GameDB>(*_logService, *_dbExecutor, std::move(dataSource));

			// _gameDB->DropAndCreateCharacterDB().Get();

			_finalizers.emplace_back([this]()
				{
					_gameDB->Stop();
				});

			LOGI(*_logService, "initialize GameDB DONE")
		};
		initializeGameDB();
	}

	void GameServer::InitializeServices()
	{
		auto initializeLoginService = [this]()
		{
			_loginService = std::make_shared<login::LoginService>(_serviceLocator, *_gameDB);
			_serviceLocator.SetLoginService(_loginService.get());

			LOGI(*_logService, "initialize LoginService DONE")
		};
		initializeLoginService();

		auto initializeWorldService = [this]()
		{
			for (const WorldConfig& worldConfig : _config.worlds)
			{
				_worldServices.push_back(std::make_shared<world::WorldService>(
					worldConfig.id, "127.0.0.1", *_gameDB));
			}

			for (const std::shared_ptr<IWorldService>& worldService : _worldServices)
			{
				_serviceLocator.SetWorldService(worldService->Id(), worldService.get());
			}
		};
		initializeWorldService();
	}

	void GameServer::InitializeServers()
	{
		auto initializeLoginServer = [this]()
		{
			_loginServer = std::make_shared<login::LoginServer>(_serviceLocator, *_networkExecutor);
			_loginServer->Start();

			_finalizers.emplace_back([this]()
				{
					_loginServer->Stop();
				});

			LOGI(*_logService, "initialize LoginServer DONE")
		};
		initializeLoginServer();

		auto initializeGatewayServer = [this]()
		{
			_gatewayServer = std::make_shared<gateway::GatewayServer>(_serviceLocator, *_networkExecutor);
			_gatewayServer->Start();

			_finalizers.emplace_back([this]()
				{
					_gatewayServer->Stop();
				});

			LOGI(*_logService, "initialize GatewayServer DONE")
		};
		initializeGatewayServer();

		auto initializeZoneServer = [this]()
		{
			_zoneServer = std::make_shared<zone::ZoneServer>(_serviceLocator, *_networkExecutor,
				7878, std::make_shared<zone::Zone>(_serviceLocator));
			_zoneServer->Start();

			_finalizers.emplace_back([this]()
				{
					_zoneServer->Stop();
				});

			LOGI(*_logService, "initialize ZoneServer DONE")
		};
		initializeZoneServer();
	}

	void GameServer::Finalize()
	{
		for (const auto& finalizer : _finalizers | srv::reverse)
		{
			finalizer();
		}
	}
}

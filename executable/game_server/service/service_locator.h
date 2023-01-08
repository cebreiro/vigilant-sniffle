#pragma once
#include "lib/common/log/log_macro.h"
#include "service/login_service_interface.h"
#include "service/world_service_interface.h"

namespace cebreiro::gamedata
{
	class GameDataSource;
}

namespace cebreiro::gamedb
{
	class GameDB;
}

namespace cebreiro
{
	class IServiceLocator
	{
	public:
		virtual ~IServiceLocator() = default;

		[[nodiscard]]
		virtual auto LogService() const -> ILogService& = 0;

		[[nodiscard]]
		virtual auto GameDataSource() const -> gamedata::GameDataSource& = 0;

		[[nodiscard]]
		virtual auto LoginService() const -> ILoginService& = 0;

		[[nodiscard]]
		virtual auto WorldService(int8_t worldId) const -> IWorldService& = 0;

		[[nodiscard]]
		virtual auto WorldServices() const -> const std::vector<IWorldService*>& = 0;

		[[nodiscard]]
		virtual auto FindWorldService(int8_t worldId) const -> IWorldService* = 0;
	};

	class ServiceLocator : public IServiceLocator
	{
	public:
		auto LogService() const -> ILogService& override;
		auto GameDataSource() const -> gamedata::GameDataSource& override;
		auto LoginService() const -> ILoginService& override;
		auto WorldService(int8_t worldId) const -> IWorldService& override;
		auto WorldServices() const -> const std::vector<IWorldService*>& override;

		auto FindWorldService(int8_t worldId) const -> IWorldService* override;

		void SetLogService(ILogService* service);
		void SetGameDataSource(gamedata::GameDataSource* source);
		void SetLoginService(ILoginService* service);
		void SetWorldService(int8_t worldId, IWorldService* service);

	private:
		ILogService* _logService = nullptr;
		gamedata::GameDataSource* _gameDataSource = nullptr;

		ILoginService* _loginService = nullptr;

		std::vector<IWorldService*> _worldServices;
		std::unordered_map<int8_t, IWorldService*> _worldServiceIdIndexer;
	};
}
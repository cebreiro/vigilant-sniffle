#pragma once
#include "lib/common/log/log_macro.h"
#include "lib/game_service/service_locator_interface.h"


namespace cebreiro
{
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
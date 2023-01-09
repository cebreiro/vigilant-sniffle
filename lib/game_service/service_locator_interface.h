#pragma once
#include <cstdint>
#include <vector>
#include "lib/game_service/login/login_service_interface.h"
#include "lib/game_service/world/world_service_interface.h"

namespace cebreiro
{
	class ILogService;
}

namespace cebreiro::gamedata
{
	class GameDataSource;
}

namespace cebreiro
{
	class ILoginService;
	class IWorldService;
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
}
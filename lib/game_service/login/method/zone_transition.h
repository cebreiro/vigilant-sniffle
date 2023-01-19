#pragma once
#include <cstdint>
#include "lib/common/execution/future.h"
#include "lib/game_service/login/auth_token.h"

namespace cebreiro::service
{
	struct ZoneTransitionMethod
	{
		virtual ~ZoneTransitionMethod() = default;

		struct ConfigureParam
		{
			int32_t zoneId = -1;
			int64_t characterId = -1;
		};

		[[nodiscard]]
		virtual auto ConfigureZoneTransitionState(AuthToken authToken, ConfigureParam param) -> Future<bool> = 0;

		struct ConsumeResult
		{
			bool success = false;
			int64_t accountId = -1;
			int8_t worldId = -1;
			int32_t zoneId = -1;
			int64_t characterId = -1;
		};

		[[nodiscard]]
		virtual auto ConsumeZoneTransitionState(AuthToken authToken) -> Future<ConsumeResult> = 0;
	};
}
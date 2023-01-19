#pragma once
#include <cstdint>
#include "lib/common/execution/future.h"
#include "lib/game_service/login/auth_token.h"

namespace cebreiro::service
{
	struct GatewayTransitionMethod
	{
		virtual ~GatewayTransitionMethod() = default;

		[[nodiscard]]
		virtual auto ConfigureGatewayTransitionState(AuthToken authToken, int8_t world) -> Future<bool> = 0;

		struct ConsumeResult
		{
			bool success = false;
			int64_t accountId = -1;
			int8_t worldId = -1;
		};

		[[nodiscard]]
		virtual auto ConsumeGatewayTransitionState(AuthToken authToken) -> Future<ConsumeResult> = 0;
	};
}
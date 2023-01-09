#pragma once
#include <cstdint>
#include <utility>
#include <optional>
#include "lib/common/execution/future.h"
#include "lib/game_base/db/account.h"
#include "lib/game_service/login/login_result.h"

namespace cebreiro
{
	class ILoginService
	{
	public:
		virtual ~ILoginService() {}

		[[nodiscard]]
		virtual auto Login(std::string account, std::string password) -> Future<LoginResult> = 0;

		[[nodiscard]]
		virtual auto Logout(AuthToken authToken, int64_t accountId) -> Future<void> = 0;

		virtual void AddLoginReleaseEventHandler(const std::function<void(int64_t)>& handler) = 0;


		[[nodiscard]]
		virtual auto SetWorldId(AuthToken authToken, int8_t world) -> Future<bool> = 0;

		[[nodiscard]]
		virtual auto FindUser(AuthToken authToken) -> Future<std::optional<std::pair<int64_t, int8_t>>> = 0;
	};
}
#pragma once
#include <cstdint>
#include <string>
#include "lib/common/execution/future.h"
#include "lib/game_service/login/auth_token.h"

namespace cebreiro::service
{
	struct LoginMethod
	{
		virtual ~LoginMethod() = default;

		struct LoginResult
		{
			enum class ErrorCode
			{
				Success,
				FailInvalid,
				FailDuplicated,
				FailTimeout,
			};

			ErrorCode errorCode = ErrorCode::Success;
			AuthToken authToken;
			int64_t accountId = -1;
		};

		[[nodiscard]]
		virtual auto Login(std::string account, std::string password) -> Future<LoginResult> = 0;

		[[nodiscard]]
		virtual auto Logout(AuthToken authToken, int64_t accountId) -> Future<void> = 0;
	};
}
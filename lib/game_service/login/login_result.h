#pragma once
#include <cstdint>
#include "lib/game_service/login/auth_token.h"

namespace cebreiro
{
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
}
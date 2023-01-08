#pragma once
#include "lib/common/execution/future.h"
#include "lib/game_base/db/account.h"

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
		int64_t accountId = -1;
	};

	class ILoginService
	{
	public:
		virtual ~ILoginService() {}

		[[nodiscard]]
		virtual auto Login(std::string account, std::string password) -> Future<LoginResult> = 0;

		[[nodiscard]]
		virtual auto Logout(int64_t accountId) -> Future<void> = 0;

		[[nodiscard]]
		virtual auto AddGatewayAuthentication(int64_t accountId, int8_t world, std::array<int32_t, 2> token) -> Future<bool> = 0;

		[[nodiscard]]
		virtual auto PopGatewayAuthentication(std::array<int32_t, 2> token) -> Future<std::optional<std::pair<int64_t, int8_t>>> = 0;
	};
}
#pragma once
#include "lib/common/execution/thread_pool.h"
#include "lib/game_service/login/auth_token.h"

namespace cebreiro::network
{
	class Session;
}

namespace cebreiro::login
{
	enum class LoginSessionState
	{
		Connected,
		LoggedIn,
		WorldSelectOk,
	};

	struct LoginSessionContext
	{
		std::shared_ptr<network::Session> session;
		ThreadPool::Strand strand;
		LoginSessionState state = LoginSessionState::Connected;
		AuthToken authToken;
		int64_t accountId = -1;
	};
}
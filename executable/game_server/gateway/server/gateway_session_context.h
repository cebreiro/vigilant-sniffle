#pragma once
#include "lib/common/execution/thread_pool.h"
#include "lib/game_db/entity/character.h"

namespace cebreiro::network
{
	class Session;
}

namespace cebreiro
{
	class IWorldService;
}

namespace cebreiro::gateway
{
	enum class GatewaySessionState
	{
		Connected,
		VersionChecked,
		Authorized,
		GamePlaying,
	};

	struct GatewaySessionContext
	{
		std::shared_ptr<network::Session> session;
		ThreadPool::Strand strand;
		GatewaySessionState state = GatewaySessionState::Connected;
		AuthToken authToken;
		int64_t accountId = -1;
		int8_t worldId = -1;
		std::vector<gamedb::Character> characters;
	};
}
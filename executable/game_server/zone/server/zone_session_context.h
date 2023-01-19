#pragma once
#include "lib/common/execution/thread_pool.h"
#include "lib/game_service/login/auth_token.h"
#include "zone/game/object/game_object_id.h"

namespace cebreiro::zone
{
	class Zone;
}

namespace cebreiro::zone
{
	enum class ZoneSessionState
	{
		Connected,
		Authorized,
	};

	struct ZoneSessionContext
	{
		std::shared_ptr<network::Session> session;
		ThreadPool::Strand strand;
		ZoneSessionState state = ZoneSessionState::Connected;
		Zone& zone;
		AuthToken authToken;
		int64_t accountId = -1;
		int64_t characterId = -1;
		int32_t stage = -1;
		GameObjectId gameObjectId;
	};
}
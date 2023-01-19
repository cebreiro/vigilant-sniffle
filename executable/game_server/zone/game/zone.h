#pragma once
#include "lib/common/execution/thread_pool.h"
#include "lib/game_base/type/object.h"
#include "lib/game_db/entity/character.h"
#include "zone/game/object/game_object_id.h"
#include "zone/message/sc/login_accept.h"

namespace cebreiro
{
	class IServiceLocator;
}

namespace cebreiro::network
{
	class Session;
}

namespace cebreiro::zone::msg
{
	class ZoneEventRequestHandler;
	class ZoneEventRequestAsyncHandler;
}

namespace cebreiro::zone
{
	class Stage;
}

namespace cebreiro::zone
{
	class Zone
	{
	public:
		Zone(const IServiceLocator& serviceLocator);
		~Zone();

		auto SpawnPlayer(gamedb::Character character, std::shared_ptr<network::Session> session)
			-> Future<std::optional<msg::LoginAccept>>;
		auto PostEvent(int32_t stageId, std::unique_ptr<msg::ZoneEventRequestHandler> event) -> Future<bool>;
		auto PostEvent(int32_t stageId, std::unique_ptr<msg::ZoneEventRequestAsyncHandler> event) -> Future<bool>;

		auto Id() const -> int32_t;
		auto WorldId() const -> int8_t;

		auto CreateMoverId() -> int32_t;
		auto CreateGameObjectId(type::Object type) -> GameObjectId;

		auto GetServiceLocator() const -> const IServiceLocator&;

	private:
		auto FindStage(int32_t stageId) -> Stage*;

	private:
		const IServiceLocator& _serviceLocator;
		ThreadPool::Strand _strand;

		std::vector<std::unique_ptr<Stage>> _stages;

		int32_t _nextMoverId = 1;
		int32_t _nextObjectId = 1;
	};
}

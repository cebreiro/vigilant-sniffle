#include "zone.h"

#include "event/zone/zone_event_request_handler.h"
#include "lib/common/execution/executor_await.h"
#include "lib/common/execution/future_await.h"
#include "lib/network/session.h"
#include "zone/game/event/zone/zone_event_request_handler.h"
#include "zone/game/object/player.h"
#include "zone/game/stage/stage.h"
#include "zone/game/component/movement_component.h"
#include "zone/game/object/game_object.h"
#include "zone/message/sc/login_accept.h"

namespace cebreiro::zone
{
	Zone::Zone(const IServiceLocator& serviceLocator)
		: _serviceLocator(serviceLocator)
		, _strand(ThreadPool::GetInstance().MakeStrand())
	{
		_stages.push_back(std::make_unique<Stage>());
	}

	Zone::~Zone()
	{
	}

	auto Zone::SpawnPlayer(gamedb::Character character, std::shared_ptr<network::Session> session)
		-> Future<std::optional<msg::LoginAccept>>
	{
		co_await _strand;

		Stage* stage = FindStage(character.base.stage);
		if (!stage)
		{
			co_return std::nullopt;
		}

		GameObjectId id = CreateGameObjectId(type::Object::Player);
		auto player = std::make_shared<Player>(*this, id, character, std::move(session));

		if (!stage->SpawnPlayer(player))
		{
			co_return std::nullopt;
		}

		co_return msg::LoginAccept(*player, this->Id(), stage->Id());
	}

	auto Zone::PostEvent(int32_t stageId, std::unique_ptr<msg::ZoneEventRequestHandler> event) -> Future<bool>
	{
		co_await _strand;

		Stage* stage = FindStage(stageId);
		if (!stage)
		{
			co_return false;
		}

		GameObject* source = stage->Find(event->GetSourceId());

		if (!source)
		{
			co_return false;
		}

		assert(stage == &source->GetStage());

		event->HandleEvent(*this, *stage, *source);
		co_return true;
	}

	auto Zone::PostEvent(int32_t stageId, std::unique_ptr<msg::ZoneEventRequestAsyncHandler> event) -> Future<bool>
	{
		co_await _strand;

		Stage* stage = FindStage(stageId);
		if (!stage)
		{
			co_return false;
		}

		GameObject* source = stage->Find(event->GetSourceId());

		if (!source)
		{
			co_return false;
		}

		assert(stage == &source->GetStage());

		co_await event->HandleEvent(*this, *stage, source->shared_from_this());
		co_return true;
	}

	auto Zone::Id() const -> int32_t
	{
		return 401;
	}

	auto Zone::WorldId() const -> int8_t
	{
		return 2;
	}

	auto Zone::CreateMoverId() -> int32_t
	{
		return _nextMoverId++;
	}

	auto Zone::CreateGameObjectId(type::Object type) -> GameObjectId
	{
		return GameObjectId(type, _nextObjectId++);
	}

	auto Zone::GetServiceLocator() const -> const IServiceLocator&
	{
		return _serviceLocator;
	}

	auto Zone::FindStage(int32_t stageId) -> Stage*
	{
		auto iter = sr::find_if(_stages, [stageId](const std::unique_ptr<Stage>& stage)
			{
				return stage->Id() == stageId;
			});
		return iter != _stages.end() ? iter->get() : nullptr;
	}
}

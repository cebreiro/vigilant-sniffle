#pragma once
#include "zone/game/event/zone/zone_event_request_handler.h"

namespace cebreiro::zone::msg
{
	class StateAllRequest : public ZoneEventRequestHandler
	{
	public:
		static constexpr ZoneEventType TYPE = ZoneEventType::REQUEST_ALL_STATE;

	public:
		StateAllRequest(ZoneEventType type, GameObjectId sourceId, GameObjectId targetId);

		void HandleEvent(Zone& zone, Stage& stage, GameObject& source) override;
	};
}
#pragma once
#include "zone/game/event/zone/zone_event_request_handler.h"

namespace cebreiro::zone::msg
{
	class ItemArchiveInit : public ZoneEventRequestHandler
	{
	public:
		static constexpr ZoneEventType TYPE = ZoneEventType::ITEMARCHIVE_INIT;

	public:
		ItemArchiveInit(ZoneEventType type, GameObjectId sourceId, GameObjectId targetId);

		void HandleEvent(Zone& zone, Stage& stage, GameObject& source) override;
	};
}
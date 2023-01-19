#pragma once
#include "zone/game/event/zone/zone_event_request_handler.h"
#include "zone/game/event/zone/zone_event_request_handler_factory.h"

namespace cebreiro::zone::msg
{
	class ItemArchive : public ZoneEventRequestHandler
	{
	public:
		static constexpr ZoneEventType TYPE = ZoneEventType::ITEMARCHIVEMSG;

	public:
		ItemArchive(ZoneEventType type, GameObjectId sourceId, GameObjectId targetId);

		void HandleEvent(Zone& zone, Stage& stage, GameObject& source) override;
		void Deserialize(gamebase::PacketReader& reader) override;

	private:
		ZoneEventType _subType = ZoneEventType::None;
		ZoneEventRequestHandlerFactory::result_type _subHandler;
	};
}

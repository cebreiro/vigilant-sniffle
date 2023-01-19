#include "item_archive_init.h"

#include "zone/game/event/zone/zone_event_request_handler_factory.h"

namespace cebreiro::zone::msg
{
	[[maybe_unused]]
	static ZoneEventRequestHandlerFactory::AutoRegistry<ItemArchiveInit> registry;

	ItemArchiveInit::ItemArchiveInit(ZoneEventType type, GameObjectId sourceId, GameObjectId targetId)
		: ZoneEventRequestHandler(type, sourceId, targetId)
	{
	}

	void ItemArchiveInit::HandleEvent(Zone& zone, Stage& stage, GameObject& source)
	{
		(void)zone;
		(void)stage;
		(void)source;
	}
}

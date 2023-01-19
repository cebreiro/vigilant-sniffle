#include "state_all_request.h"

#include "zone/game/event/zone/zone_event_request_handler_factory.h"

namespace cebreiro::zone::msg
{
	[[maybe_unused]]
	static ZoneEventRequestHandlerFactory::AutoRegistry<StateAllRequest> registry;

	StateAllRequest::StateAllRequest(ZoneEventType type, GameObjectId sourceId, GameObjectId targetId)
		: ZoneEventRequestHandler(type, sourceId, targetId)
	{
	}

	void StateAllRequest::HandleEvent(Zone& zone, Stage& stage, GameObject& source)
	{
		(void)zone;
		(void)stage;
		(void)source;
	}
}

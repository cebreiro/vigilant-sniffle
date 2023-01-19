#pragma once
#include "zone/message/cs/trigger_event.h"
#include "zone/server/handler/cs_message_handler.h"

namespace cebreiro::zone
{
	class TriggerEventHandler : public CSMessageAsyncHandler<msg::TriggerEvent>
	{
	public:
		auto OnMessage(const IServiceLocator& locator, ZoneSessionContext& context,
			const msg::TriggerEvent& message) -> Future<void> override;
	};
}
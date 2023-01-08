#include "cs_message_handler_auto_registry.h"

#include "gateway/server/handler/cs_message_handler_container.h"

namespace cebreiro::gateway
{
	CSMessageHandlerAutoRegistry::CSMessageHandlerAutoRegistry(CSMessageType type, ICSMessageHandler* handler)
	{
		CSMessageHandlerContainer::Add(type, handler);
	}

	CSMessageHandlerAutoRegistry::CSMessageHandlerAutoRegistry(CSMessageType type, ICSMessageAsyncHandler* handler)
	{
		CSMessageHandlerContainer::Add(type, handler);
	}
}
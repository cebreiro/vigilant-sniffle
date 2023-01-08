#include "cs_message_handler_auto_registry.h"

#include "login/server/handler/cs_message_handler_container.h"

namespace cebreiro::login
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

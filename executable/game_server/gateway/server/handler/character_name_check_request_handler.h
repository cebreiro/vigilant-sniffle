#pragma once
#include "gateway/message/cs/character_name_check_request.h"
#include "gateway/server/handler/cs_message_handler.h"

namespace cebreiro::gateway
{
	class CharacterNameCheckRequestHandler : public CSMessageAsyncHandler<CharacterNameCheckRequest>
	{
	public:
		auto OnMessage(const IServiceLocator& locator, GatewaySessionContext& context,
			const CharacterNameCheckRequest& message) -> Future<void> override;
	};
}
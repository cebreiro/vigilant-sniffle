#pragma once
#include "gateway/message/cs/character_list_request.h"
#include "gateway/server/handler/cs_message_handler.h"

namespace cebreiro::gateway
{
	class CharacterListRequestHandler : public CSMessageHandler<CharacterListRequest>
	{
	public:
		void OnMessage(const IServiceLocator& locator, GatewaySessionContext& context,
			const CharacterListRequest& message) override;
	};
}
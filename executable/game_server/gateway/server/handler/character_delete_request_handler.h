#pragma once
#include "gateway/message/cs/character_delete_request.h"
#include "gateway/server/handler/cs_message_handler.h"

namespace cebreiro::gateway
{
	class CharacterDeleteRequestHandler : public CSMessageAsyncHandler<CharacterDeleteRequest>
	{
	public:
		auto OnMessage(const IServiceLocator& locator, GatewaySessionContext& context,
			const CharacterDeleteRequest& message) -> Future<void> override;

	private:
		void OnError(const IServiceLocator& locator, const GatewaySessionContext& context, std::string log);
	};
}
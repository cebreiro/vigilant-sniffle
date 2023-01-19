#pragma once
#include "gateway/message/cs/character_select_request.h"
#include "gateway/server/handler/cs_message_handler.h"

namespace cebreiro::gateway
{
	class CharacterSelectRequestHandler : public CSMessageAsyncHandler<CharacterSelectRequest>
	{
	public:
		auto OnMessage(const IServiceLocator& locator, GatewaySessionContext& context,
			const CharacterSelectRequest& message) -> Future<void> override;

	private:
		void OnError(const IServiceLocator& locator, const GatewaySessionContext& context, std::string log) const;
	};
}
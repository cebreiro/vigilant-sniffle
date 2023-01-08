#pragma once
#include "lib/game_db/entity/character.h"
#include "gateway/message/cs/character_create_request.h"
#include "gateway/server/handler/cs_message_handler.h"

namespace cebreiro::gateway
{
	class CharacterCreateRequestHandler : public CSMessageAsyncHandler<CharacterCreateRequest>
	{
	public:
		auto OnMessage(const IServiceLocator& locator, GatewaySessionContext& context,
			const CharacterCreateRequest& message) -> Future<void> override;

	private:
		void OnError(const IServiceLocator& locator, const GatewaySessionContext& context, std::string log);

		auto CreateCharacter(const IServiceLocator& locator, const GatewaySessionContext& context,
			const CharacterCreateRequest& message) const -> Future<gamedb::Character>;
	};
}
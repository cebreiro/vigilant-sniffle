#include "character_name_check_request_handler.h"

#include "lib/common/execution/future_await.h"
#include "lib/network/session.h"
#include "service/service_locator.h"
#include "gateway/server/handler/cs_message_handler_auto_registry.h"
#include "gateway/server/gateway_session_context.h"
#include "gateway/message/sc/character_name_check_response.h"

namespace cebreiro::gateway
{
	[[maybe_unused]]
	static CSMessageHandlerAutoRegistryT<CharacterNameCheckRequestHandler> registry;

	auto CharacterNameCheckRequestHandler::OnMessage(const IServiceLocator& locator, GatewaySessionContext& context,
		const CharacterNameCheckRequest& message) -> Future<void>
	{
		network::Session& session = *context.session;

		if (context.state != GatewaySessionState::Authorized)
		{
			LOGE(locator.LogService(), 
				std::format("invalid request. state: {}, session: {}",
					static_cast<int32_t>(context.state), session.Id().Value(), session.RemoteAddress()))

			session.Send(CharacterNameCheckResponse(false, message.name).Serialize());
			co_return;
		}

		bool result = co_await locator.WorldService(context.worldId).CheckCharacterNameUsable(message.name)
			.ConfigureAwait(context.strand);

		session.Send(CharacterNameCheckResponse(result, message.name).Serialize());
	}
}

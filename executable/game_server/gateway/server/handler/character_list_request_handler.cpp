#include "character_list_request_handler.h"

#include "lib/common/log/log_macro.h"
#include "lib/network/session.h"
#include "gateway/server/gateway_session_context.h"
#include "gateway/message/sc/character_list_response.h"
#include "gateway/server/handler/cs_message_handler_auto_registry.h"
#include "service/service_locator.h"

namespace cebreiro::gateway
{
	[[maybe_unused]]
	static CSMessageHandlerAutoRegistryT<CharacterListRequestHandler> registry;

	void CharacterListRequestHandler::OnMessage(const IServiceLocator& locator, GatewaySessionContext& context,
		[[maybe_unused]] const CharacterListRequest& message)
	{
		network::Session& session = *context.session;

		if (context.state != GatewaySessionState::Authorized)
		{
			LOGE(locator.LogService(),
				std::format("invalid request session[{}, {}]",
					session.Id().Value(), session.RemoteAddress()));
			return;
		}

		CharacterListResponse response(locator.GameDataSource(), context.characters);
		session.Send(response.Serialize());
	}
}

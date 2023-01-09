#include "client_version_request_handler.h"

#include "lib/common/execution/future.h"
#include "lib/common/log/log_macro.h"
#include "lib/network/session.h"
#include "lib/game_service/service_locator_interface.h"
#include "config/server_constant.h"
#include "gateway/message/sc/client_version_response.h"
#include "gateway/server/gateway_session_context.h"
#include "gateway/server/handler/cs_message_handler_auto_registry.h"


namespace cebreiro::gateway
{
	[[maybe_unused]]
	static CSMessageHandlerAutoRegistryT<ClientVersionRequestHandler> registry;

	void ClientVersionRequestHandler::OnMessage(const IServiceLocator& locator, GatewaySessionContext& context,
		const ClientVersionRequest& message)
	{
		network::Session& session = *context.session;

		if (context.state != GatewaySessionState::Connected)
		{
			OnError(locator, context,
				std::format("invalid state. session[{}:{}]",
					session.Id().Value(), session.RemoteAddress()));
			return;
		}

		if (message.version != ServerConstant::GAME_VERSION)
		{
			OnError(locator, context,
				std::format("invalid game version. session[{}:{}], version: {}",
					session.Id().Value(), session.RemoteAddress(), message.version));
			return;
		}

		context.state = GatewaySessionState::VersionChecked;

		session.Send(ClientVersionResponse(true).Serialize());
	}

	void ClientVersionRequestHandler::OnError(const IServiceLocator& locator, const GatewaySessionContext& context, std::string log)
	{
		LOGW(locator.LogService(), std::move(log))

		context.session->Send(ClientVersionResponse(false).Serialize());

		Delay(3000).Then([session = context.session]()
			{
				session->Close();
			});
	}
}

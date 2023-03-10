#include "authentication_request_handler.h"

#include "lib/common/execution/future_await.h"
#include "lib/common/log/log_macro.h"
#include "lib/network/session.h"
#include "lib/game_service/service_locator_interface.h"
#include "gateway/server/gateway_session_context.h"
#include "gateway/server/handler/cs_message_handler_auto_registry.h"
#include "gateway/message/sc/authentication_response.h"


namespace cebreiro::gateway
{
	[[maybe_unused]]
	static CSMessageHandlerAutoRegistryT<AuthenticationRequestHandler> registry;

	auto AuthenticationRequestHandler::OnMessage(const IServiceLocator& locator, GatewaySessionContext& context,
		const AuthenticationRequest& message) -> Future<void>
	{
		network::Session& session = *context.session;

		AuthToken authToken(message.key1, message.key2);

		const auto& result = co_await locator.LoginService().ConsumeGatewayTransitionState(authToken)
			.ConfigureAwait(context.strand);

		if (context.state != GatewaySessionState::VersionChecked)
		{
			OnError(locator, context,
				std::format("invalid request session[{}, {}]",
					session.Id().Value(), session.RemoteAddress()));
			co_return;
		}

		if (!result.success)
		{
			OnError(locator, context,
				std::format("fail to authorize session[{}, {}]",
					session.Id().Value(), session.RemoteAddress()));
			co_return;
		}

		context.state = GatewaySessionState::Authorized;
		context.authToken = authToken;
		context.accountId = result.accountId;
		context.worldId = result.worldId;
		context.characters = co_await locator.WorldService(context.worldId).GetCharacters(context.accountId)
			.ConfigureAwait(context.strand);

		session.Send(AuthenticationResponse(true).Serialize());
		
		co_return;
	}

	void AuthenticationRequestHandler::OnError(const IServiceLocator& locator, const GatewaySessionContext& context, std::string log)
	{
		LOGE(locator.LogService(), std::move(log))

		context.session->Send(AuthenticationResponse(false).Serialize());

		Delay(3000).Then([session = context.session]()
			{
				session->Close();
			});
	}
}

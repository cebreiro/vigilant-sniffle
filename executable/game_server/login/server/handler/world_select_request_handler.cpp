#include "world_select_request_handler.h"

#include "lib/common/execution/future_await.h"
#include "lib/common/log/log_macro.h"
#include "lib/network/session.h"
#include "lib/game_service/service_locator_interface.h"
#include "login/message/sc/world_select_response.h"
#include "login/server/login_session_context.h"
#include "login/server/handler/cs_message_handler_auto_registry.h"


namespace cebreiro::login
{
	[[maybe_unused]]
	static CSMessageHandlerAutoRegistryT<WorldSelectRequestHandler> registry;

	auto WorldSelectRequestHandler::OnMessage(const IServiceLocator& locator, LoginSessionContext& context,
		const WorldSelectRequest& message) -> Future<void>
	{
		network::Session& session = *context.session;

		IWorldService* worldService = locator.FindWorldService(message.worldId);
		if (!worldService)
		{
			LOGE(locator.LogService(),
				std::format("fail to find world service. world_id: {}, session[{}:{}]",
					message.worldId, session.Id().Value(), session.RemoteAddress()))
			co_return;
		}

		bool result = co_await locator.LoginService().SetWorldId(context.authToken, message.worldId)
			.ConfigureAwait(context.strand);

		if (!result)
		{
			OnError(locator, context, 
				std::format("fail to login world auth. session[{}:{}]",
					session.Id().Value(), session.RemoteAddress()));
			co_return;
		}

		if (context.state != LoginSessionState::LoggedIn)
		{
			OnError(locator, context, 
				std::format("invalid request from session[{}:{}]",
					session.Id().Value(), session.RemoteAddress()));
			co_return;
		}

		context.state = LoginSessionState::WorldSelectOk;

		session.Send(WorldSelectResponse(message.worldId, context.authToken.ToIntArray()).Serialize());

		constexpr uint64_t cheatSessionAutoDisconnectMilliSeconds = 3000;
		co_await Delay(cheatSessionAutoDisconnectMilliSeconds);

		session.Close();
	}

	void WorldSelectRequestHandler::OnError(const IServiceLocator& locator, const LoginSessionContext& context,
		std::string log)
	{
		network::Session& session = *context.session;

		LOGE(locator.LogService(), std::move(log))

		(void)locator.LoginService().Logout(context.authToken, context.accountId);
		session.Close();
	}
}

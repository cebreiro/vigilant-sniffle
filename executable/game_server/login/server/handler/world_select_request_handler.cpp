#include "world_select_request_handler.h"

#include "lib/common/execution/future_await.h"
#include "lib/network/session.h"
#include "login/message/sc/world_select_response.h"
#include "login/server/login_session_context.h"
#include "service/service_locator.h"
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

		std::array<int32_t, 2> authenticationToken = [&message]() -> std::array<int32_t, 2>
		{
			// doesn't use client key
			std::array result{ message.key1, message.key2 };

			std::random_device rnd;
			result[0] = rnd();
			result[1] = rnd();

			return result;
		}();

		bool result = co_await locator.LoginService().AddGatewayAuthentication(context.accountId, message.worldId, authenticationToken)
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

		session.Send(WorldSelectResponse(message.worldId, authenticationToken).Serialize());

		constexpr uint64_t cheatSessionAutoDisconnectMilliSeconds = 3000;
		co_await Delay(cheatSessionAutoDisconnectMilliSeconds);

		session.Close();
	}

	void WorldSelectRequestHandler::OnError(const IServiceLocator& locator, const LoginSessionContext& context,
		std::string log)
	{
		network::Session& session = *context.session;

		LOGE(locator.LogService(), std::move(log))

		(void)locator.LoginService().Logout(context.accountId);
		session.Close();
	}
}

#include "logout_request_handler.h"

#include "lib/common/log/log_macro.h"
#include "lib/network/session.h"
#include "lib/game_service/service_locator_interface.h"
#include "login/server/login_session_context.h"
#include "login/server/handler/cs_message_handler_auto_registry.h"


namespace cebreiro::login
{
	[[maybe_unused]]
	static CSMessageHandlerAutoRegistryT<LogoutRequestHandler> registry;

	void LogoutRequestHandler::OnMessage(const IServiceLocator& locator, LoginSessionContext& context,
		[[maybe_unused]] const LogoutRequest& message)
	{
		network::Session& session = *context.session;

		if (context.state != LoginSessionState::LoggedIn)
		{
			LOGE(locator.LogService(),
				std::format("invalid logout state. state: {}, session[{}:{}]",
					static_cast<int32_t>(context.state), session.Id().Value(), session.RemoteAddress()))
		}

		session.Close();
	}
}

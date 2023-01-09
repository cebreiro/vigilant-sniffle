#include "login_pass_request_handler.h"

#include "lib/network/session.h"
#include "login/server/login_session_context.h"
#include "login/server/handler/cs_message_handler_auto_registry.h"


namespace cebreiro::login
{
	[[maybe_unused]]
	static CSMessageHandlerAutoRegistryT<LoginPassRequestHandler> registry;

	void LoginPassRequestHandler::OnMessage(const IServiceLocator& locator, LoginSessionContext& context,
		const LoginPassRequest& message)
	{
		(void)locator;
		(void)message;

		context.session->Close();
	}
}

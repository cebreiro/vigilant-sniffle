#include "login_request_handler.h"

#include "lib/common/execution/future_await.h"
#include "lib/network/session.h"
#include "login/message/sc/login_fail_response.h"
#include "login/message/sc/world_list_notify.h"
#include "login/server/login_session_context.h"
#include "login/server/handler/cs_message_handler_auto_registry.h"
#include "service/service_locator.h"

namespace cebreiro::login
{
	[[maybe_unused]]
	static CSMessageHandlerAutoRegistryT<LoginRequestHandler> registry;

	auto LoginRequestHandler::OnMessage(const IServiceLocator& locator, LoginSessionContext& context,
		const LoginRequest& message) -> Future<void>
	{
		network::Session& session = *context.session;

		LoginResult result = 
			co_await locator.LoginService().Login(message.account, message.password)
			.ConfigureAwait(context.strand);
		
		if (context.state != LoginSessionState::Connected)
		{
			LOGE(locator.LogService(),
				std::format("invalid login request(maybe double) from session[{}:{}]",
					session.Id().Value(), session.RemoteAddress()))
			co_return;
		}

		if (result.errorCode != LoginResult::ErrorCode::Success)
		{
			LoginFailReason failReason = [](LoginResult::ErrorCode errorCode)
			{
				switch (errorCode)
				{
				case LoginResult::ErrorCode::FailDuplicated: 
					return LoginFailReason::ReleaseExistingConnection;
				case LoginResult::ErrorCode::FailTimeout:
					return LoginFailReason::CantConnectServer;
				default:
					return LoginFailReason::InvalidIDPassword;
				}
			}(result.errorCode);

			session.Send(LoginFailResponse(failReason).Serialize());
			co_return;
		}

		context.state = LoginSessionState::LoggedIn;
		context.accountId = result.accountId;

		session.Send(WorldListNotify(locator.WorldServices()).Serialize());
	}
}

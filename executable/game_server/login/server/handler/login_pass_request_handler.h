#pragma once
#include "login/message/cs/login_pass_request.h"
#include "login/server/handler/cs_message_handler.h"

namespace cebreiro::login
{
	class LoginPassRequestHandler : public CSMessageHandler<LoginPassRequest>
	{
	public:
		void OnMessage(const IServiceLocator& locator, LoginSessionContext& context,
			const LoginPassRequest& message) override;
	};
}
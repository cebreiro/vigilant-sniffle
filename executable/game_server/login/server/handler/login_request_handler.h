#pragma once
#include "login/message/cs/login_request.h"
#include "login/server/handler/cs_message_handler.h"

namespace cebreiro::login
{
	class LoginRequestHandler : public CSMessageAsyncHandler<LoginRequest>
	{
	public:
		auto OnMessage(const IServiceLocator& locator, LoginSessionContext& context,
			const LoginRequest& message) -> Future<void> override;
	};
}
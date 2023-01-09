#pragma once
#include "login/message/cs/logout_request.h"
#include "login/server/handler/cs_message_handler.h"

namespace cebreiro::login
{
	class LogoutRequestHandler : public CSMessageHandler<LogoutRequest>
	{
	public:
		void OnMessage(const IServiceLocator& locator, LoginSessionContext& context,
			const LogoutRequest& message) override;
	};
}
#pragma once
#include "gateway/message/cs/authentication_request.h"
#include "gateway/server/handler/cs_message_handler.h"

namespace cebreiro::gateway
{
	class AuthenticationRequestHandler : public CSMessageAsyncHandler<AuthenticationRequest>
	{
	public:
		auto OnMessage(const IServiceLocator& locator, GatewaySessionContext& context,
			const AuthenticationRequest& message) -> Future<void> override;

	private:
		void OnError(const IServiceLocator& locator, const GatewaySessionContext& context, std::string log);
	};
}
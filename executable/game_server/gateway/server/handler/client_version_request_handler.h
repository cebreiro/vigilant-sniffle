#pragma once
#include "gateway/message/cs/client_version_request.h"
#include "gateway/server/handler/cs_message_handler.h"

namespace cebreiro::gateway
{
	class ClientVersionRequestHandler : public CSMessageHandler<ClientVersionRequest>
	{
	public:
		void OnMessage(const IServiceLocator& locator, GatewaySessionContext& context, 
			const ClientVersionRequest& message) override;

	private:
		void OnError(const IServiceLocator& locator, const GatewaySessionContext& context, std::string log);
	};
}
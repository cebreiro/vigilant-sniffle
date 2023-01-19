#pragma once
#include "zone/message/cs/login.h"
#include "zone/server/handler/cs_message_handler.h"

namespace cebreiro::zone
{
	class LoginHandler : public CSMessageAsyncHandler<msg::Login>
	{
	public:
		auto OnMessage(const IServiceLocator& locator, ZoneSessionContext& context,
			const msg::Login& message) -> Future<void> override;

	private:
		void OnError(const IServiceLocator& locator, const ZoneSessionContext& context, std::string log);
	};
}
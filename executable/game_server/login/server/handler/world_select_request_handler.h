#pragma once
#include "login/message/cs/world_select_request.h"
#include "login/server/handler/cs_message_handler.h"

namespace cebreiro::login
{
	class WorldSelectRequestHandler : public CSMessageAsyncHandler<WorldSelectRequest>
	{
	public:
		auto OnMessage(const IServiceLocator& locator, LoginSessionContext& context,
			const WorldSelectRequest& message) -> Future<void> override;

	private:
		static void OnError(const IServiceLocator& locator, const LoginSessionContext& context, std::string log);
	};
}
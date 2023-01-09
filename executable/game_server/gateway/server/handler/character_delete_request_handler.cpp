#include "character_delete_request_handler.h"

#include "lib/common/execution/future_await.h"
#include "lib/common/log/log_macro.h"
#include "lib/network/session.h"
#include "gateway/message/sc/character_delete_response.h"
#include "gateway/server/gateway_session_context.h"
#include "gateway/server/handler/cs_message_handler_auto_registry.h"
#include "service/service_locator.h"

namespace cebreiro::gateway
{
	[[maybe_unused]]
	static CSMessageHandlerAutoRegistryT<CharacterDeleteRequestHandler> registry;

	auto CharacterDeleteRequestHandler::OnMessage(const IServiceLocator& locator, GatewaySessionContext& context,
		const CharacterDeleteRequest& message) -> Future<void>
	{
		network::Session& session = *context.session;

		if (context.state != GatewaySessionState::Authorized)
		{
			OnError(locator, context,
				std::format("invalid request. state: {}, session[{}:{}]",
					static_cast<int32_t>(context.state), session.Id().Value(), session.RemoteAddress()));
			co_return;
		}

		if (!message.IsValid())
		{
			OnError(locator, context,
				std::format("message is invalid. session:[{}:{}]",
					session.Id().Value(), session.RemoteAddress()));
			co_return;
		}

		std::optional<int64_t> cid = [&]() -> std::optional<int64_t>
		{
			auto iter = sr::find_if(context.characters, [&](const gamedb::Character& character)
				{
					return character.base.slot == message.slot;
				});
			return iter != context.characters.end() ? std::optional(iter->base.id) : std::nullopt;
		}();

		if (!cid.has_value())
		{
			OnError(locator, context,
				std::format("fail to find character from slot: {}, session[{}:{}]",
					message.slot, session.Id().Value(), session.RemoteAddress()));

			co_return;
		}

		if (! co_await locator.WorldService(context.worldId).DeleteCharacter(*cid))
		{
			OnError(locator, context,
				std::format("fail to delete character. slot: {}, session[{}: {}]",
					message.slot, session.Id().Value(), session.RemoteAddress()));
			co_return;
		}

		context.characters.clear();
		context.characters = co_await locator.WorldService(context.worldId).GetCharacters(context.accountId);

		context.session->Send(CharacterDeleteResponse(true).Serialize());
	}

	void CharacterDeleteRequestHandler::OnError(const IServiceLocator& locator, const GatewaySessionContext& context, std::string log)
	{
		LOGE(locator.LogService(), std::move(log))

		context.session->Send(CharacterDeleteResponse(false).Serialize());
	}
}

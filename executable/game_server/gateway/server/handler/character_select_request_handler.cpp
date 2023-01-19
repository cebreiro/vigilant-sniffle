#include "character_select_request_handler.h"

#include "lib/common/log/log_macro.h"
#include "lib/common/execution/future_await.h"
#include "lib/network/session.h"
#include "lib/game_service/service_locator_interface.h"
#include "gateway/server/gateway_session_context.h"
#include "gateway/server/handler/cs_message_handler_auto_registry.h"
#include "gateway/message/sc/character_select_response.h"

namespace cebreiro::gateway
{
	[[maybe_unused]]
	static CSMessageHandlerAutoRegistryT<CharacterSelectRequestHandler> registry;

	auto CharacterSelectRequestHandler::OnMessage(const IServiceLocator& locator, GatewaySessionContext& context,
		const CharacterSelectRequest& message) -> Future<void>
	{
		network::Session& session = *context.session;

		if (context.state != GatewaySessionState::Authorized)
		{
			OnError(locator, context,
				std::format("invalid request. state: {}, session[{}:{}]",
					static_cast<int32_t>(context.state), session.Id().Value(), session.RemoteAddress()));
			co_return;
		}

		const gamedb::Character* character = [&]() -> const gamedb::Character*
		{
			auto iter = sr::find_if(context.characters, [slot = message.slot](const gamedb::Character& character)
				{
					return character.base.slot == slot;
				});
			return iter != context.characters.end() ? &(*iter) : nullptr;
		}();

		if (!character)
		{
			OnError(locator, context,
				std::format("fail to find character. slot: {}state: {}, session[{}:{}]",
					message.slot, static_cast<int32_t>(context.state), session.Id().Value(), session.RemoteAddress()));
			co_return;
		}

		bool result = co_await locator.LoginService().ConfigureZoneTransitionState(context.authToken, {
			.zoneId = character->base.zone,
			.characterId = character->base.id
			})
		.ConfigureAwait(context.strand);

		if (!result)
		{
			OnError(locator, context,
				std::format("fail to configure zone transition. character: {}, session[{}:{}]",
					character->base.name, session.Id().Value(), session.RemoteAddress()));
			co_return;
		}

		EndPoint destination("127.0.0.1", 7878);
		std::string key = context.authToken.ToString();
		int32_t auth = -1;

		session.Send(CharacterSelectResponse::Success(auth, key, destination).Serialize());
	}

	void CharacterSelectRequestHandler::OnError(const IServiceLocator& locator, const GatewaySessionContext& context,
		std::string log) const
	{
		LOGE(locator.LogService(), std::move(log))

		context.session->Send(CharacterSelectResponse::Failure().Serialize());
	}
}

#include "login_handler.h"

#include "lib/common/log/log_macro.h"
#include "lib/common/execution/future_await.h"
#include "lib/game_service/service_locator_interface.h"
#include "lib/network/session.h"
#include "zone/game/zone.h"
#include "zone/message/sc/login_reject.h"
#include "zone/server/zone_session_context.h"
#include "zone/server/handler/cs_message_handler_auto_registry.h"

namespace cebreiro::zone
{
	[[maybe_unused]]
	static CSMessageHandlerAutoRegistryT<LoginHandler> registry;

	auto LoginHandler::OnMessage(const IServiceLocator& locator, ZoneSessionContext& context,
		const msg::Login& message) -> Future<void>
	{
		network::Session& session = *context.session;
		Zone& zone = context.zone;

		AuthToken authToken = AuthToken::FromString(message.token.key);

		const auto& result = co_await locator.LoginService().ConsumeZoneTransitionState(authToken)
			.ConfigureAwait(context.strand);

		if (!result.success)
		{
			OnError(locator, context,
				std::format("fail to consume zone transition state. token: {}, session[{}:{}]",
					authToken.ToString(), session.Id().Value(), session.RemoteAddress()));

			co_return;
		}

		if (context.state != ZoneSessionState::Connected)
		{
			OnError(locator, context,
				std::format("invalid state. session[{}:{}]",
					session.Id().Value(), session.RemoteAddress()));

			co_return;
		}

		if (zone.Id() != result.zoneId)
		{
			OnError(locator, context,
				std::format("invalid zone id. current: {}, destination: {}, session[{}:{}]",
					zone.Id(), result.zoneId, session.Id().Value(), session.RemoteAddress()));

			co_return;
		}

		std::optional<gamedb::Character> character = co_await locator.WorldService(zone.WorldId()).GetCharacter(result.characterId)
			.ConfigureAwait(context.strand);

		if (!character.has_value())
		{
			OnError(locator, context,
				std::format("fail to get character. world: {}, cid: {}, session[{}:{}]",
					zone.WorldId(), result.characterId, session.Id().Value(), session.RemoteAddress()));

			co_return;
		}

		if (zone.Id() != character->base.zone)
		{
			OnError(locator, context,
				std::format("invalid zone id. current: {}, db: {}, session[{}:{}]",
					zone.Id(), character->base.zone, session.Id().Value(), session.RemoteAddress()));

			co_return;
		}

		std::optional<msg::LoginAccept> loginAccept = co_await zone.SpawnPlayer(character.value(), context.session)
			.ConfigureAwait(context.strand);

		if (!loginAccept.has_value())
		{
			OnError(locator, context,
				std::format("fail to spawn character. world: {}, zone: {}, cid: {}, session[{}:{}]",
					zone.WorldId(), zone.Id(), result.characterId, session.Id().Value(), session.RemoteAddress()));

			co_return;
		}

		context.state = ZoneSessionState::Authorized;
		context.accountId = result.accountId;
		context.characterId = result.characterId;
		context.stage = loginAccept->GetStage();
		context.gameObjectId = loginAccept->GetId();

		session.Send(loginAccept->Serialize());

		co_return;
	}

	void LoginHandler::OnError(const IServiceLocator& locator, const ZoneSessionContext& context, std::string log)
	{
		LOGE(locator.LogService(), std::move(log));

		context.session->Send(msg::LoginReject("internal error occur").Serialize());

		Delay(3000).Then([session = context.session]()
			{
				session->Close();
			});
	}
}

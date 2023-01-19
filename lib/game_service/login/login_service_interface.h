#pragma once
#include "lib/game_service/login/method/login.h"
#include "lib/game_service/login/method/gateway_transition.h"
#include "lib/game_service/login/method/zone_transition.h"
#include "lib/game_service/login/event/login_service_event.h"

namespace cebreiro
{
	struct ILoginService
		: service::LoginMethod
		, service::GatewayTransitionMethod
		, service::ZoneTransitionMethod
	{
		virtual void AddSubscriber(LoginServiceEventType type, const std::function<void(const LoginServiceEvent&)>& handler) = 0;
	};
}
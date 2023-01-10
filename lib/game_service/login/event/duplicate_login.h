#pragma once
#include <cstdint>
#include "lib/game_service/login/event/login_service_event.h"

namespace cebreiro
{
	struct DuplicateLogin : LoginServiceEvent
	{
		static constexpr LoginServiceEventType TYPE = LoginServiceEventType::DuplicateLogin;

		DuplicateLogin() = default;
		explicit DuplicateLogin(int64_t accountId);

		void Deserialize(StreamReader& reader) override;
		void Serialize(StreamWriter& writer) const override;
		auto Type() const -> LoginServiceEventType override;

		int64_t accountId = -1;
	};
}
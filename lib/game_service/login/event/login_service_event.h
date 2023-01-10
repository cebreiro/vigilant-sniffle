#pragma once
#include "lib/common/stream/deserializable.h"
#include "lib/common/stream/serializable.h"
#include "lib/game_service/login/event/login_service_event_type.h"

namespace cebreiro
{
	class LoginServiceEvent : public IDeserializable, public ISerializable
	{
	public:
		virtual ~LoginServiceEvent();

		virtual auto Type() const -> LoginServiceEventType = 0;
	};
}
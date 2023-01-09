#pragma once
#include "lib/common/stream/deserializable.h"
#include "login/message/cs/cs_message_type.h"

namespace cebreiro::login
{
	struct LoginPassRequest : IDeserializable
	{
		static constexpr CSMessageType TYPE = CSMessageType::LoginPassRequest;

		void Deserialize(StreamReader& reader) override;
	};
}

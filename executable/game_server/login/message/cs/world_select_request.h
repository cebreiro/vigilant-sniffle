#pragma once
#include "lib/common/stream/deserializable.h"
#include "login/message/cs/cs_message_type.h"

namespace cebreiro::login
{
	struct WorldSelectRequest : IDeserializable
	{
		static constexpr CSMessageType TYPE = CSMessageType::WorldSelectRequest;

		void Deserialize(StreamReader& reader) override;

		int32_t key1 = 0;
		int32_t key2 = 0;
		int8_t worldId = -1;
	};
}
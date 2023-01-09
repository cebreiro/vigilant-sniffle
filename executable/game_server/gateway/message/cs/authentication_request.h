#pragma once
#include "lib/game_base/network/packet_deserializable.h"
#include "gateway/message/cs/cs_message_type.h"

namespace cebreiro::gateway
{
	struct AuthenticationRequest : gamebase::IPacketDeserializable
	{
		static constexpr CSMessageType TYPE = CSMessageType::AuthenticationRequest;

		void Deserialize(gamebase::PacketReader& reader) override;

		int32_t key1 = 0;
		int32_t key2 = 0;
		std::pair<int32_t, int32_t> unk = {};
	};
}
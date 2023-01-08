#pragma once
#include "lib/game_base/network/packet_deserializable.h"
#include "gateway/message/cs/cs_message_type.h"

namespace cebreiro::gateway
{
	struct AuthenticationRequest : gamebase::IPacketDeserializable
	{
		static constexpr CSMessageType TYPE = CSMessageType::AuthenticationRequest;

		void Deserialize(gamebase::PacketReader& reader) override;

		std::array<int32_t, 2> token = {};
		std::pair<int32_t, int32_t> unk = {};
	};
}
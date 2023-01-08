#pragma once
#include "lib/game_base/network/packet_deserializable.h"
#include "gateway/message/cs/cs_message_type.h"

namespace cebreiro::gateway
{
	struct ClientVersionRequest : gamebase::IPacketDeserializable
	{
		static constexpr CSMessageType TYPE = CSMessageType::ClientVersionRequest;

		void Deserialize(gamebase::PacketReader& reader) override;

		int32_t version = -1;
	};
}
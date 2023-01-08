#pragma once
#include "lib/game_base/network/packet_deserializable.h"
#include "gateway/message/cs/cs_message_type.h"

namespace cebreiro::gateway
{
	struct CharacterListRequest : gamebase::IPacketDeserializable
	{
		static constexpr CSMessageType TYPE = CSMessageType::CharacterListRequest;

		void Deserialize(gamebase::PacketReader& reader) override;
	};
}
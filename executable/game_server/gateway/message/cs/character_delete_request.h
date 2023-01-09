#pragma once
#include "lib/game_base/network/packet_deserializable.h"
#include "gateway/message/cs/cs_message_type.h"

namespace cebreiro::gateway
{
	struct CharacterDeleteRequest : gamebase::IPacketDeserializable
	{
		static constexpr CSMessageType TYPE = CSMessageType::CharacterDeleteRequest;

		bool IsValid() const;
		void Deserialize(gamebase::PacketReader& reader) override;

		int8_t slot;
	};
}
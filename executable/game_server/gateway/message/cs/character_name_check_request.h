#pragma once
#include "lib/game_base/network/packet_deserializable.h"
#include "gateway/message/cs/cs_message_type.h"

namespace cebreiro::gamedata
{
	class GameDataSource;
}

namespace cebreiro::gateway
{
	struct CharacterNameCheckRequest : gamebase::IPacketDeserializable
	{
		static constexpr CSMessageType TYPE = CSMessageType::CharacterNameCheckRequest;

		void Deserialize(gamebase::PacketReader& reader) override;

		std::string name;
	};
}
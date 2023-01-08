#pragma once
#include "lib/game_base/network/packet_deserializable.h"
#include "gateway/message/cs/cs_message_type.h"

namespace cebreiro::gamedata
{
	class GameDataSource;
}

namespace cebreiro::gateway
{
	struct CharacterCreateRequest : gamebase::IPacketDeserializable
	{
		static constexpr CSMessageType TYPE = CSMessageType::CharacterCreateRequest;

		bool IsValid(const gamedata::GameDataSource& dataSource) const;
		void Deserialize(gamebase::PacketReader& reader) override;

		std::string name;
		int8_t gender = 0;
		int32_t str = 0;
		int32_t dex = 0;
		int32_t accr = 0;
		int32_t health = 0;
		int32_t intell = 0;
		int32_t wis = 0;
		int32_t will = 0;
		int32_t stat_point = 0;
		int8_t water = 0;
		int8_t fire = 0;
		int8_t lightning = 0;
		int32_t unk01 = 0;
		int32_t hairColor = 0;
		int32_t skinColor = 0;
		int32_t face = 0;
		int32_t hair = 0;
		int32_t jacketId = 0;
		int32_t glovesModelId = 0;
		int32_t pantsId = 0;
		int32_t shoesId = 0;
		int32_t unk02 = 0;
		int32_t unk03 = 0;
		int32_t unk04 = 0;
		int32_t unk05 = 0;
		int32_t unk06 = 0;
		int32_t unk07 = 0;
		int32_t unk08 = 0;
		int32_t unk09 = 0;
		int32_t unk10 = 0;
		int32_t unk11 = 0;
		int32_t unk12 = 0;
		int32_t unk13 = 0;
		int32_t unk14 = 0;
		int32_t unk15 = 0;
		int32_t unk16 = 0;
		int32_t unk17 = 0;
		int32_t job1 = 0;

		int8_t slot = -1;
	};
}
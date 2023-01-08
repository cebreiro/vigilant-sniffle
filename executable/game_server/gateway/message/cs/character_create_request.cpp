#include "character_create_request.h"

#include "lib/game_base/network/packet_reader.h"
#include "lib/game_data/game_data_source.h"
#include "lib/game_data/utility/item.h"
#include "lib/game_data/generated/item_clothes.h"

namespace cebreiro::gateway
{
	namespace
	{
		bool IsWearable(const gamedata::ItemClothes* data, type::Job job, int32_t level)
		{
			if (!data)
			{
				return false;
			}

			return gamedata::IsWearable(*data, job, level);
		}
	}

	bool CharacterCreateRequest::IsValid(const gamedata::GameDataSource& dataSource) const
	{
		if (slot < 0 || slot > 4)
		{
			return false;
		}

		constexpr int32_t minStatValue = 5;
		if (str < minStatValue || dex < minStatValue || accr < minStatValue ||
			health < minStatValue || intell < minStatValue || wis < minStatValue || will < minStatValue)
		{
			return false;
		}

		int32_t sumOfStat = str + dex + accr + health + intell + wis + will + water + fire;
		(void)sumOfStat;

		const auto& itemClothesTable = dataSource.Get<gamedata::ItemClothesTable>();

		type::Job job = static_cast<type::Job>(job1);
		constexpr int32_t level = 1;

		if (!IsWearable(itemClothesTable->Find(jacketId), job, level))
		{
			return false;
		}

		if (!IsWearable(itemClothesTable->Find(pantsId), job, level))
		{
			return false;
		}

		if (!IsWearable(itemClothesTable->Find(shoesId), job, level))
		{
			return false;
		}

		return true;
	}

	void CharacterCreateRequest::Deserialize(gamebase::PacketReader& reader)
	{
		StreamReader objectReader = reader.ReadObject();
		{
			name = objectReader.ReadString(32);
			gender = static_cast<int8_t>(objectReader.ReadInt32());
			str = objectReader.ReadInt32();
			dex = objectReader.ReadInt32();
			accr = objectReader.ReadInt32();
			health = objectReader.ReadInt32();
			intell = objectReader.ReadInt32();
			wis = objectReader.ReadInt32();
			will = objectReader.ReadInt32();
			water = static_cast<int8_t>(objectReader.ReadInt32());
			fire = static_cast<int8_t>(objectReader.ReadInt32());
			lightning = static_cast<int8_t>(objectReader.ReadInt32());
			unk01 = objectReader.ReadInt32();
			hairColor = objectReader.ReadInt32();
			skinColor = objectReader.ReadInt32();
			face = objectReader.ReadInt32();
			hair = objectReader.ReadInt32();
			jacketId = objectReader.ReadInt32();
			[[maybe_unused]] int32_t gloves_model_id = objectReader.ReadInt32();
			pantsId = objectReader.ReadInt32();
			shoesId = objectReader.ReadInt32();
			unk02 = objectReader.ReadInt32();
			unk03 = objectReader.ReadInt32();
			unk04 = objectReader.ReadInt32();
			unk05 = objectReader.ReadInt32();
			unk06 = objectReader.ReadInt32();
			unk07 = objectReader.ReadInt32();
			unk08 = objectReader.ReadInt32();
			unk09 = objectReader.ReadInt32();
			unk10 = objectReader.ReadInt32();
			unk11 = objectReader.ReadInt32();
			unk12 = objectReader.ReadInt32();
			unk13 = objectReader.ReadInt32();
			unk14 = objectReader.ReadInt32();
			unk15 = objectReader.ReadInt32();
			unk16 = objectReader.ReadInt32();
			unk17 = objectReader.ReadInt32();
			job1 = objectReader.ReadInt32();
		}
		slot = static_cast<int8_t>(reader.ReadInt32());
	}
}

/**********************************************************
         AUTO GENERATED FILE BY sox_code_generator
                   DO NOT EDIT THIS FILE
**********************************************************/
#include "item_edible.h"

#include "lib/common/stream/stream_reader.h"
#include "lib/game_base/data/sox/sox_file.h"
#include "lib/game_data/game_data_registry.h"

namespace cebreiro::gamedata
{
	[[maybe_unused]]
	static GameDataRegistry<ItemEdibleTable> registry;

	ItemEdible::ItemEdible(StreamReader& reader)
	{
		index = reader.ReadInt32();
		name = reader.ReadString(reader.ReadUInt16());
		generate = reader.ReadInt32();
		explanation = reader.ReadString(reader.ReadUInt16());
		invenWidth = reader.ReadInt32();
		invenHeight = reader.ReadInt32();
		maxOverlapCount = reader.ReadInt32();
		rarity = reader.ReadInt32();
		price = reader.ReadInt32();
		modelID = reader.ReadInt32();
		modelColor = reader.ReadInt32();
		dropSound = reader.ReadInt32();
		useQuickSlot = reader.ReadInt32();
		oneMoreItem = reader.ReadInt32();
		equipPos = reader.ReadInt32();
		eatClass = reader.ReadInt32();
		effect1 = reader.ReadInt32();
		effectDuration1 = reader.ReadInt32();
		effectValue1 = reader.ReadInt32();
		effectPercent1 = reader.ReadInt32();
		effectReservedA1 = reader.ReadInt32();
		effectReservedB1 = reader.ReadInt32();
		effect2 = reader.ReadInt32();
		effectDuration2 = reader.ReadInt32();
		effectValue2 = reader.ReadInt32();
		effectPercent2 = reader.ReadInt32();
		effectReservedA2 = reader.ReadInt32();
		effectReservedB2 = reader.ReadInt32();
		effect3 = reader.ReadInt32();
		effectDuration3 = reader.ReadInt32();
		effectValue3 = reader.ReadInt32();
		effectPercent3 = reader.ReadInt32();
		effectReservedA3 = reader.ReadInt32();
		effectReservedB3 = reader.ReadInt32();
		effect4 = reader.ReadInt32();
		effectDuration4 = reader.ReadInt32();
		effectValue4 = reader.ReadInt32();
		effectPercent4 = reader.ReadInt32();
		effectReservedA4 = reader.ReadInt32();
		effectReservedB4 = reader.ReadInt32();
		effectSound = reader.ReadInt32();
		ableToSell = reader.ReadInt32();
		ableToTrade = reader.ReadInt32();
		ableToDrop = reader.ReadInt32();
		ableToDestroy = reader.ReadInt32();
		ableToStorage = reader.ReadInt32();
		conID = reader.ReadInt32();
		conRangeTime = reader.ReadInt32();
		reservedParam1 = reader.ReadInt32();
		reservedParam2 = reader.ReadInt32();
		reservedParam3 = reader.ReadInt32();
		reservedParam4 = reader.ReadInt32();
		reservedParam5 = reader.ReadInt32();
		reservedParam6 = reader.ReadInt32();
		reservedParam7 = reader.ReadInt32();
	}

	void ItemEdibleTable::LoadFromFile(const std::filesystem::path& path)
	{
		gamebase::SoxFile fileData(path / "item_edible.sox");
		StreamReader reader(fileData.gameData.data(), fileData.gameData.size());

		_vector.reserve(fileData.rowCount);
		for (int32_t i = 0; i < fileData.rowCount; ++i)
		{
			_vector.emplace_back(reader);
		}

		for (const ItemEdible& data : _vector)
		{
			_umap[data.index] = &data;
		}
	}

	auto ItemEdibleTable::Find(int32_t index) const -> const ItemEdible*
	{
		auto iter = _umap.find(index);
		return iter != _umap.end() ? iter->second : nullptr;
	}

	auto ItemEdibleTable::Get() const -> const std::vector<ItemEdible>&
	{
		return _vector;
	}
}

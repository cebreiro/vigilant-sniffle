/**********************************************************
         AUTO GENERATED FILE BY sox_code_generator
                   DO NOT EDIT THIS FILE
**********************************************************/
#include "item_clothes.h"

#include "lib/common/stream/stream_reader.h"
#include "lib/game_base/data/sox/sox_file.h"
#include "lib/game_data/game_data_registry.h"

namespace cebreiro::gamedata
{
	[[maybe_unused]]
	static GameDataRegistry<ItemClothesTable> registry;

	ItemClothes::ItemClothes(StreamReader& reader)
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
		armorClass = reader.ReadInt32();
		defense = reader.ReadInt32();
		protection = reader.ReadInt32();
		equipEffect1 = reader.ReadInt32();
		equipEffectValue1 = reader.ReadInt32();
		equipEffect2 = reader.ReadInt32();
		equipEffectValue2 = reader.ReadInt32();
		equipEffect3 = reader.ReadInt32();
		equipEffectValue3 = reader.ReadInt32();
		equipEffect4 = reader.ReadInt32();
		equipEffectValue4 = reader.ReadInt32();
		constraint1 = reader.ReadInt32();
		constraint2 = reader.ReadInt32();
		constraint3 = reader.ReadInt32();
		constraint4 = reader.ReadInt32();
		constraint5 = reader.ReadInt32();
		constraint6 = reader.ReadInt32();
		constraint7 = reader.ReadInt32();
		constraint8 = reader.ReadInt32();
		constraintValue1 = reader.ReadInt32();
		constraintValue2 = reader.ReadInt32();
		constraintValue3 = reader.ReadInt32();
		constraintValue4 = reader.ReadInt32();
		constraintValue5 = reader.ReadInt32();
		constraintValue6 = reader.ReadInt32();
		constraintValue7 = reader.ReadInt32();
		constraintValue8 = reader.ReadInt32();
		constraintOR1 = reader.ReadInt32();
		constraintOR2 = reader.ReadInt32();
		constraintOR3 = reader.ReadInt32();
		constraintOR4 = reader.ReadInt32();
		constraintOR5 = reader.ReadInt32();
		constraintOR6 = reader.ReadInt32();
		constraintOR7 = reader.ReadInt32();
		ableToSell = reader.ReadInt32();
		ableToTrade = reader.ReadInt32();
		ableToDrop = reader.ReadInt32();
		ableToDestroy = reader.ReadInt32();
		ableToStorage = reader.ReadInt32();
	}

	void ItemClothesTable::LoadFromFile(const std::filesystem::path& path)
	{
		gamebase::SoxFile fileData(path / "item_clothes.sox");
		StreamReader reader(fileData.gameData.data(), fileData.gameData.size());

		_vector.reserve(fileData.rowCount);
		for (int32_t i = 0; i < fileData.rowCount; ++i)
		{
			_vector.emplace_back(reader);
		}

		for (const ItemClothes& data : _vector)
		{
			_umap[data.index] = &data;
		}
	}

	auto ItemClothesTable::Find(int32_t index) const -> const ItemClothes*
	{
		auto iter = _umap.find(index);
		return iter != _umap.end() ? iter->second : nullptr;
	}

	auto ItemClothesTable::Get() const -> const std::vector<ItemClothes>&
	{
		return _vector;
	}
}

/**********************************************************
         AUTO GENERATED FILE BY sox_code_generator
                   DO NOT EDIT THIS FILE
**********************************************************/
#include "item_base_attack.h"

#include "lib/common/stream/stream_reader.h"
#include "lib/game_base/data/sox/sox_file.h"
#include "lib/game_data/game_data_registry.h"

namespace cebreiro::gamedata
{
	[[maybe_unused]]
	static GameDataRegistry<ItemBaseAttackTable> registry;

	ItemBaseAttack::ItemBaseAttack(StreamReader& reader)
	{
		index = reader.ReadInt32();
		motionCategory = reader.ReadInt32();
		dexBased = reader.ReadInt32();
		minimumDamage = reader.ReadInt32();
		maximumDamage = reader.ReadInt32();
		attackDelay = reader.ReadInt32();
		divDamage = reader.ReadInt32();
		divDamageDelay = reader.ReadInt32();
		combo = reader.ReadInt32();
		attackRange = reader.ReadInt32();
		hitMaterial = reader.ReadInt32();
		hitFX1 = reader.ReadInt32();
		hitFX2 = reader.ReadInt32();
		hitFX3 = reader.ReadInt32();
		hitFX4 = reader.ReadInt32();
		hitFX5 = reader.ReadInt32();
		hitFX6 = reader.ReadInt32();
		hitFX7 = reader.ReadInt32();
		hitFX8 = reader.ReadInt32();
		hitFX9 = reader.ReadInt32();
		hitFX10 = reader.ReadInt32();
	}

	void ItemBaseAttackTable::LoadFromFile(const std::filesystem::path& path)
	{
		gamebase::SoxFile fileData(path / "ITEM_BASE_ATTACK.sox");
		StreamReader reader(fileData.gameData.data(), fileData.gameData.size());

		_vector.reserve(fileData.rowCount);
		for (int32_t i = 0; i < fileData.rowCount; ++i)
		{
			_vector.emplace_back(reader);
		}

		for (const ItemBaseAttack& data : _vector)
		{
			_umap[data.index] = &data;
		}
	}

	auto ItemBaseAttackTable::Find(int32_t index) const -> const ItemBaseAttack*
	{
		auto iter = _umap.find(index);
		return iter != _umap.end() ? iter->second : nullptr;
	}

	auto ItemBaseAttackTable::Get() const -> const std::vector<ItemBaseAttack>&
	{
		return _vector;
	}
}

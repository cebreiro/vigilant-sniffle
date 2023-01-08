/**********************************************************
         AUTO GENERATED FILE BY sox_code_generator
                   DO NOT EDIT THIS FILE
**********************************************************/
#include "monster_item.h"

#include "lib/common/stream/stream_reader.h"
#include "lib/game_base/data/sox/sox_file.h"
#include "lib/game_data/game_data_registry.h"

namespace cebreiro::gamedata
{
	[[maybe_unused]]
	static GameDataRegistry<MonsterItemTable> registry;

	MonsterItem::MonsterItem(StreamReader& reader)
	{
		index = reader.ReadInt32();
		itemGenFrequency = reader.ReadInt32();
		itemsetGenFrequency = reader.ReadInt32();
		rareItemGenFrequency = reader.ReadInt32();
		rareItemsetGenFrequency = reader.ReadInt32();
		itemGoldMod = reader.ReadInt32();
		itemGoldMin = reader.ReadInt32();
		itemGoldMax = reader.ReadInt32();
		item01 = reader.ReadInt32();
		item01Mod = reader.ReadInt32();
		item02 = reader.ReadInt32();
		item02Mod = reader.ReadInt32();
		item03 = reader.ReadInt32();
		item03Mod = reader.ReadInt32();
		item04 = reader.ReadInt32();
		item04Mod = reader.ReadInt32();
		item05 = reader.ReadInt32();
		item05Mod = reader.ReadInt32();
		item06 = reader.ReadInt32();
		item06Mod = reader.ReadInt32();
		item07 = reader.ReadInt32();
		item07Mod = reader.ReadInt32();
		item08 = reader.ReadInt32();
		item08Mod = reader.ReadInt32();
		item09 = reader.ReadInt32();
		item09Mod = reader.ReadInt32();
		item10 = reader.ReadInt32();
		item10Mod = reader.ReadInt32();
		item11 = reader.ReadInt32();
		item11Mod = reader.ReadInt32();
		item12 = reader.ReadInt32();
		item12Mod = reader.ReadInt32();
		item13 = reader.ReadInt32();
		item13Mod = reader.ReadInt32();
		item14 = reader.ReadInt32();
		item14Mod = reader.ReadInt32();
		item15 = reader.ReadInt32();
		item15Mod = reader.ReadInt32();
		item16 = reader.ReadInt32();
		item16Mod = reader.ReadInt32();
		item17 = reader.ReadInt32();
		item17Mod = reader.ReadInt32();
		item18 = reader.ReadInt32();
		item18Mod = reader.ReadInt32();
		item19 = reader.ReadInt32();
		item19Mod = reader.ReadInt32();
		item20 = reader.ReadInt32();
		item20Mod = reader.ReadInt32();
		item21 = reader.ReadInt32();
		item21Mod = reader.ReadInt32();
		item22 = reader.ReadInt32();
		item22Mod = reader.ReadInt32();
		item23 = reader.ReadInt32();
		item23Mod = reader.ReadInt32();
		item24 = reader.ReadInt32();
		item24Mod = reader.ReadInt32();
		item25 = reader.ReadInt32();
		item25Mod = reader.ReadInt32();
		item26 = reader.ReadInt32();
		item26Mod = reader.ReadInt32();
		item27 = reader.ReadInt32();
		item27Mod = reader.ReadInt32();
		item28 = reader.ReadInt32();
		item28Mod = reader.ReadInt32();
		item29 = reader.ReadInt32();
		item29Mod = reader.ReadInt32();
		item30 = reader.ReadInt32();
		item30Mod = reader.ReadInt32();
		itemset01 = reader.ReadInt32();
		itemset01Mod = reader.ReadInt32();
		itemset02 = reader.ReadInt32();
		itemset02Mod = reader.ReadInt32();
		itemset03 = reader.ReadInt32();
		itemset03Mod = reader.ReadInt32();
		itemset04 = reader.ReadInt32();
		itemset04Mod = reader.ReadInt32();
		itemset05 = reader.ReadInt32();
		itemset05Mod = reader.ReadInt32();
		itemset06 = reader.ReadInt32();
		itemset06Mod = reader.ReadInt32();
		itemset07 = reader.ReadInt32();
		itemset07Mod = reader.ReadInt32();
		itemset08 = reader.ReadInt32();
		itemset08Mod = reader.ReadInt32();
		itemset09 = reader.ReadInt32();
		itemset09Mod = reader.ReadInt32();
		itemset10 = reader.ReadInt32();
		itemset10Mod = reader.ReadInt32();
		rareItem01 = reader.ReadInt32();
		rareItem01Mod = reader.ReadInt32();
		rareItem02 = reader.ReadInt32();
		rareItem02Mod = reader.ReadInt32();
		rareItem03 = reader.ReadInt32();
		rareItem03Mod = reader.ReadInt32();
		rareItem04 = reader.ReadInt32();
		rareItem04Mod = reader.ReadInt32();
		rareItem05 = reader.ReadInt32();
		rareItem05Mod = reader.ReadInt32();
		rareItem06 = reader.ReadInt32();
		rareItem06Mod = reader.ReadInt32();
		rareItem07 = reader.ReadInt32();
		rareItem07Mod = reader.ReadInt32();
		rareItem08 = reader.ReadInt32();
		rareItem08Mod = reader.ReadInt32();
		rareItem09 = reader.ReadInt32();
		rareItem09Mod = reader.ReadInt32();
		rareItem10 = reader.ReadInt32();
		rareItem10Mod = reader.ReadInt32();
		rareItemset01 = reader.ReadInt32();
		rareItemset01Mod = reader.ReadInt32();
		rareItemset02 = reader.ReadInt32();
		rareItemset02Mod = reader.ReadInt32();
		rareItemset03 = reader.ReadInt32();
		rareItemset03Mod = reader.ReadInt32();
		rareItemset04 = reader.ReadInt32();
		rareItemset04Mod = reader.ReadInt32();
		rareItemset05 = reader.ReadInt32();
		rareItemset05Mod = reader.ReadInt32();
		rareItemset06 = reader.ReadInt32();
		rareItemset06Mod = reader.ReadInt32();
		rareItemset07 = reader.ReadInt32();
		rareItemset07Mod = reader.ReadInt32();
		rareItemset08 = reader.ReadInt32();
		rareItemset08Mod = reader.ReadInt32();
		rareItemset09 = reader.ReadInt32();
		rareItemset09Mod = reader.ReadInt32();
		rareItemset10 = reader.ReadInt32();
		rareItemset10Mod = reader.ReadInt32();
	}

	void MonsterItemTable::LoadFromFile(const std::filesystem::path& path)
	{
		gamebase::SoxFile fileData(path / "MONSTER_ITEM.sox");
		StreamReader reader(fileData.gameData.data(), fileData.gameData.size());

		_vector.reserve(fileData.rowCount);
		for (int32_t i = 0; i < fileData.rowCount; ++i)
		{
			_vector.emplace_back(reader);
		}

		for (const MonsterItem& data : _vector)
		{
			_umap[data.index] = &data;
		}
	}

	auto MonsterItemTable::Find(int32_t index) const -> const MonsterItem*
	{
		auto iter = _umap.find(index);
		return iter != _umap.end() ? iter->second : nullptr;
	}

	auto MonsterItemTable::Get() const -> const std::vector<MonsterItem>&
	{
		return _vector;
	}
}

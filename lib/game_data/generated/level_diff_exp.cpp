/**********************************************************
         AUTO GENERATED FILE BY sox_code_generator
                   DO NOT EDIT THIS FILE
**********************************************************/
#include "level_diff_exp.h"

#include "lib/common/stream/stream_reader.h"
#include "lib/game_base/data/sox/sox_file.h"
#include "lib/game_data/game_data_registry.h"

namespace cebreiro::gamedata
{
	[[maybe_unused]]
	static GameDataRegistry<LevelDiffExpTable> registry;

	LevelDiffExp::LevelDiffExp(StreamReader& reader)
	{
		index = reader.ReadInt32();
		partyLevelDiffFactor01 = reader.ReadInt32();
		partyLevelDiffFactor02 = reader.ReadInt32();
		partyLevelDiffFactor03 = reader.ReadInt32();
		partyLevelDiffFactor04 = reader.ReadInt32();
		partyLevelDiffFactor05 = reader.ReadInt32();
		partyLevelDiffFactor06 = reader.ReadInt32();
		partyLevelDiffFactor07 = reader.ReadInt32();
		partyLevelDiffFactor08 = reader.ReadInt32();
		partyLevelDiffFactor09 = reader.ReadInt32();
		partyLevelDiffFactor10 = reader.ReadInt32();
		partyLevelDiffFactor11 = reader.ReadInt32();
		partyLevelDiffFactor12 = reader.ReadInt32();
		monsterLevelDiffFactor01 = reader.ReadInt32();
		monsterLevelDiffFactor02 = reader.ReadInt32();
		monsterLevelDiffFactor03 = reader.ReadInt32();
		monsterLevelDiffFactor04 = reader.ReadInt32();
		monsterLevelDiffFactor05 = reader.ReadInt32();
		monsterLevelDiffFactor06 = reader.ReadInt32();
		monsterLevelDiffFactor07 = reader.ReadInt32();
		monsterLevelDiffFactor08 = reader.ReadInt32();
		monsterLevelDiffFactor09 = reader.ReadInt32();
		monsterLevelDiffFactor10 = reader.ReadInt32();
		monsterLevelDiffFactor11 = reader.ReadInt32();
		monsterLevelDiffFactor12 = reader.ReadInt32();
		rareItemDiffFactor01 = reader.ReadInt32();
		rareItemDiffFactor02 = reader.ReadInt32();
		rareItemDiffFactor03 = reader.ReadInt32();
		rareItemDiffFactor04 = reader.ReadInt32();
		rareItemDiffFactor05 = reader.ReadInt32();
		rareItemDiffFactor06 = reader.ReadInt32();
		rareItemDiffFactor07 = reader.ReadInt32();
		rareItemDiffFactor08 = reader.ReadInt32();
		rareItemDiffFactor09 = reader.ReadInt32();
		rareItemDiffFactor10 = reader.ReadInt32();
		rareItemDiffFactor11 = reader.ReadInt32();
		rareItemDiffFactor12 = reader.ReadInt32();
	}

	void LevelDiffExpTable::LoadFromFile(const std::filesystem::path& path)
	{
		gamebase::SoxFile fileData(path / "LEVEL_DIFF_EXP.sox");
		StreamReader reader(fileData.gameData.data(), fileData.gameData.size());

		_vector.reserve(fileData.rowCount);
		for (int32_t i = 0; i < fileData.rowCount; ++i)
		{
			_vector.emplace_back(reader);
		}

		for (const LevelDiffExp& data : _vector)
		{
			_umap[data.index] = &data;
		}
	}

	auto LevelDiffExpTable::Find(int32_t index) const -> const LevelDiffExp*
	{
		auto iter = _umap.find(index);
		return iter != _umap.end() ? iter->second : nullptr;
	}

	auto LevelDiffExpTable::Get() const -> const std::vector<LevelDiffExp>&
	{
		return _vector;
	}
}

/**********************************************************
         AUTO GENERATED FILE BY sox_code_generator
                   DO NOT EDIT THIS FILE
**********************************************************/
#include "monster_base.h"

#include "lib/common/stream/stream_reader.h"
#include "lib/game_base/data/sox/sox_file.h"
#include "lib/game_data/game_data_registry.h"

namespace cebreiro::gamedata
{
	[[maybe_unused]]
	static GameDataRegistry<MonsterBaseTable> registry;

	MonsterBase::MonsterBase(StreamReader& reader)
	{
		index = reader.ReadInt32();
		name = reader.ReadString(reader.ReadUInt16());
		level = reader.ReadInt32();
		exp = reader.ReadInt32();
		partyExp = reader.ReadInt32();
		race = reader.ReadInt32();
		hp = reader.ReadInt32();
		patkMin = reader.ReadInt32();
		patkMax = reader.ReadInt32();
		phrat = reader.ReadInt32();
		perat = reader.ReadInt32();
		pdefSlash = reader.ReadInt32();
		pdefBash = reader.ReadInt32();
		pdefPierce = reader.ReadInt32();
		matk = reader.ReadInt32();
		mres = reader.ReadInt32();
		elemF = reader.ReadInt32();
		elemW = reader.ReadInt32();
		elemL = reader.ReadInt32();
		speed = reader.ReadInt32();
		speedChase = reader.ReadInt32();
		debuffRes = reader.ReadInt32();
		lifetime = reader.ReadInt32();
		activationStartTime = reader.ReadInt32();
		activationEndTime = reader.ReadInt32();
		material = reader.ReadInt32();
	}

	void MonsterBaseTable::LoadFromFile(const std::filesystem::path& path)
	{
		gamebase::SoxFile fileData(path / "MONSTER_BASE.sox");
		StreamReader reader(fileData.gameData.data(), fileData.gameData.size());

		_vector.reserve(fileData.rowCount);
		for (int32_t i = 0; i < fileData.rowCount; ++i)
		{
			_vector.emplace_back(reader);
		}

		for (const MonsterBase& data : _vector)
		{
			_umap[data.index] = &data;
		}
	}

	auto MonsterBaseTable::Find(int32_t index) const -> const MonsterBase*
	{
		auto iter = _umap.find(index);
		return iter != _umap.end() ? iter->second : nullptr;
	}

	auto MonsterBaseTable::Get() const -> const std::vector<MonsterBase>&
	{
		return _vector;
	}
}

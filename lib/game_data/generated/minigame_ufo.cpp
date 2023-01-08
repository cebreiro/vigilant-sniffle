/**********************************************************
         AUTO GENERATED FILE BY sox_code_generator
                   DO NOT EDIT THIS FILE
**********************************************************/
#include "minigame_ufo.h"

#include "lib/common/stream/stream_reader.h"
#include "lib/game_base/data/sox/sox_file.h"
#include "lib/game_data/game_data_registry.h"

namespace cebreiro::gamedata
{
	[[maybe_unused]]
	static GameDataRegistry<MinigameUfoTable> registry;

	MinigameUfo::MinigameUfo(StreamReader& reader)
	{
		index = reader.ReadInt32();
		ufoname = reader.ReadString(reader.ReadUInt16());
		cost = reader.ReadInt32();
		velocity = reader.ReadInt32();
		accel = reader.ReadInt32();
		radius = reader.ReadInt32();
		mingaugespeed = reader.ReadInt32();
		maxgaugespeed = reader.ReadInt32();
		mingaugemove = reader.ReadInt32();
		maxgaugemove = reader.ReadInt32();
		maxRarity = reader.ReadInt32();
		respawnTime = reader.ReadInt32();
		item1 = reader.ReadInt32();
		item2 = reader.ReadInt32();
		item3 = reader.ReadInt32();
		item4 = reader.ReadInt32();
		item5 = reader.ReadInt32();
		item6 = reader.ReadInt32();
	}

	void MinigameUfoTable::LoadFromFile(const std::filesystem::path& path)
	{
		gamebase::SoxFile fileData(path / "MINIGAME_UFO.sox");
		StreamReader reader(fileData.gameData.data(), fileData.gameData.size());

		_vector.reserve(fileData.rowCount);
		for (int32_t i = 0; i < fileData.rowCount; ++i)
		{
			_vector.emplace_back(reader);
		}

		for (const MinigameUfo& data : _vector)
		{
			_umap[data.index] = &data;
		}
	}

	auto MinigameUfoTable::Find(int32_t index) const -> const MinigameUfo*
	{
		auto iter = _umap.find(index);
		return iter != _umap.end() ? iter->second : nullptr;
	}

	auto MinigameUfoTable::Get() const -> const std::vector<MinigameUfo>&
	{
		return _vector;
	}
}
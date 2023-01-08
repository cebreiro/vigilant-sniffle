/**********************************************************
         AUTO GENERATED FILE BY sox_code_generator
                   DO NOT EDIT THIS FILE
**********************************************************/
#include "party_add_exp.h"

#include "lib/common/stream/stream_reader.h"
#include "lib/game_base/data/sox/sox_file.h"
#include "lib/game_data/game_data_registry.h"

namespace cebreiro::gamedata
{
	[[maybe_unused]]
	static GameDataRegistry<PartyAddExpTable> registry;

	PartyAddExp::PartyAddExp(StreamReader& reader)
	{
		index = reader.ReadInt32();
		addExpFactor = reader.ReadFloat32();
	}

	void PartyAddExpTable::LoadFromFile(const std::filesystem::path& path)
	{
		gamebase::SoxFile fileData(path / "party_add_exp.sox");
		StreamReader reader(fileData.gameData.data(), fileData.gameData.size());

		_vector.reserve(fileData.rowCount);
		for (int32_t i = 0; i < fileData.rowCount; ++i)
		{
			_vector.emplace_back(reader);
		}

		for (const PartyAddExp& data : _vector)
		{
			_umap[data.index] = &data;
		}
	}

	auto PartyAddExpTable::Find(int32_t index) const -> const PartyAddExp*
	{
		auto iter = _umap.find(index);
		return iter != _umap.end() ? iter->second : nullptr;
	}

	auto PartyAddExpTable::Get() const -> const std::vector<PartyAddExp>&
	{
		return _vector;
	}
}

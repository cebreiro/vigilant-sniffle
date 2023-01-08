/**********************************************************
         AUTO GENERATED FILE BY sox_code_generator
                   DO NOT EDIT THIS FILE
**********************************************************/
#include "hairstyle.h"

#include "lib/common/stream/stream_reader.h"
#include "lib/game_base/data/sox/sox_file.h"
#include "lib/game_data/game_data_registry.h"

namespace cebreiro::gamedata
{
	[[maybe_unused]]
	static GameDataRegistry<HairstyleTable> registry;

	Hairstyle::Hairstyle(StreamReader& reader)
	{
		index = reader.ReadInt32();
		id = reader.ReadInt32();
		sex = reader.ReadInt32();
		price = reader.ReadInt32();
	}

	void HairstyleTable::LoadFromFile(const std::filesystem::path& path)
	{
		gamebase::SoxFile fileData(path / "HAIRSTYLE.sox");
		StreamReader reader(fileData.gameData.data(), fileData.gameData.size());

		_vector.reserve(fileData.rowCount);
		for (int32_t i = 0; i < fileData.rowCount; ++i)
		{
			_vector.emplace_back(reader);
		}

		for (const Hairstyle& data : _vector)
		{
			_umap[data.index] = &data;
		}
	}

	auto HairstyleTable::Find(int32_t index) const -> const Hairstyle*
	{
		auto iter = _umap.find(index);
		return iter != _umap.end() ? iter->second : nullptr;
	}

	auto HairstyleTable::Get() const -> const std::vector<Hairstyle>&
	{
		return _vector;
	}
}

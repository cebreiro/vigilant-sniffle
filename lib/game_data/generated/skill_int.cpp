/**********************************************************
         AUTO GENERATED FILE BY sox_code_generator
                   DO NOT EDIT THIS FILE
**********************************************************/
#include "skill_int.h"

#include "lib/common/stream/stream_reader.h"
#include "lib/game_base/data/sox/sox_file.h"
#include "lib/game_data/game_data_registry.h"

namespace cebreiro::gamedata
{
	[[maybe_unused]]
	static GameDataRegistry<SkillIntTable> registry;

	SkillInt::SkillInt(StreamReader& reader)
	{
		index = reader.ReadInt32();
		description = reader.ReadString(reader.ReadUInt16());
		textureid = reader.ReadInt32();
		count = reader.ReadInt32();
	}

	void SkillIntTable::LoadFromFile(const std::filesystem::path& path)
	{
		gamebase::SoxFile fileData(path / "skill_int.sox");
		StreamReader reader(fileData.gameData.data(), fileData.gameData.size());

		_vector.reserve(fileData.rowCount);
		for (int32_t i = 0; i < fileData.rowCount; ++i)
		{
			_vector.emplace_back(reader);
		}

		for (const SkillInt& data : _vector)
		{
			_umap[data.index] = &data;
		}
	}

	auto SkillIntTable::Find(int32_t index) const -> const SkillInt*
	{
		auto iter = _umap.find(index);
		return iter != _umap.end() ? iter->second : nullptr;
	}

	auto SkillIntTable::Get() const -> const std::vector<SkillInt>&
	{
		return _vector;
	}
}

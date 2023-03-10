/**********************************************************
         AUTO GENERATED FILE BY sox_code_generator
                   DO NOT EDIT THIS FILE
**********************************************************/
#include "motion_data.h"

#include "lib/common/stream/stream_reader.h"
#include "lib/game_base/data/sox/sox_file.h"
#include "lib/game_data/game_data_registry.h"

namespace cebreiro::gamedata
{
	[[maybe_unused]]
	static GameDataRegistry<MotionDataTable> registry;

	MotionData::MotionData(StreamReader& reader)
	{
		index = reader.ReadInt32();
		aniTime = reader.ReadInt32();
		hitTime = reader.ReadInt32();
		bladeStart = reader.ReadInt32();
		bladeEnd = reader.ReadInt32();
		attackSound = reader.ReadInt32();
		attackDirection = reader.ReadInt32();
		damagePercent = reader.ReadFloat32();
		damageType = reader.ReadInt32();
		damageTypePercent = reader.ReadInt32();
		targetblowFX = reader.ReadInt32();
	}

	void MotionDataTable::LoadFromFile(const std::filesystem::path& path)
	{
		gamebase::SoxFile fileData(path / "MOTION_DATA.sox");
		StreamReader reader(fileData.gameData.data(), fileData.gameData.size());

		_vector.reserve(fileData.rowCount);
		for (int32_t i = 0; i < fileData.rowCount; ++i)
		{
			_vector.emplace_back(reader);
		}

		for (const MotionData& data : _vector)
		{
			_umap[data.index] = &data;
		}
	}

	auto MotionDataTable::Find(int32_t index) const -> const MotionData*
	{
		auto iter = _umap.find(index);
		return iter != _umap.end() ? iter->second : nullptr;
	}

	auto MotionDataTable::Get() const -> const std::vector<MotionData>&
	{
		return _vector;
	}
}

/**********************************************************
         AUTO GENERATED FILE BY sox_code_generator
                   DO NOT EDIT THIS FILE
**********************************************************/
#include "pet_motion.h"

#include "lib/common/stream/stream_reader.h"
#include "lib/game_base/data/sox/sox_file.h"
#include "lib/game_data/game_data_registry.h"

namespace cebreiro::gamedata
{
	[[maybe_unused]]
	static GameDataRegistry<PetMotionTable> registry;

	PetMotion::PetMotion(StreamReader& reader)
	{
		index = reader.ReadInt32();
		name = reader.ReadString(reader.ReadUInt16());
		modelId = reader.ReadInt32();
		generateFrame = reader.ReadInt32();
		lovelyFrame = reader.ReadInt32();
		afflictFrame = reader.ReadInt32();
		eatFrame = reader.ReadInt32();
		eatTiming = reader.ReadInt32();
		hungryFrame = reader.ReadInt32();
		idle01Frame = reader.ReadInt32();
		idle02Frame = reader.ReadInt32();
		idle03Frame = reader.ReadInt32();
		idle04Frame = reader.ReadInt32();
		idle05Frame = reader.ReadInt32();
		attackFrame = reader.ReadInt32();
		attackTiming = reader.ReadInt32();
		pickupFrame = reader.ReadInt32();
		pickupTiming = reader.ReadInt32();
	}

	void PetMotionTable::LoadFromFile(const std::filesystem::path& path)
	{
		gamebase::SoxFile fileData(path / "PET_MOTION.sox");
		StreamReader reader(fileData.gameData.data(), fileData.gameData.size());

		_vector.reserve(fileData.rowCount);
		for (int32_t i = 0; i < fileData.rowCount; ++i)
		{
			_vector.emplace_back(reader);
		}

		for (const PetMotion& data : _vector)
		{
			_umap[data.index] = &data;
		}
	}

	auto PetMotionTable::Find(int32_t index) const -> const PetMotion*
	{
		auto iter = _umap.find(index);
		return iter != _umap.end() ? iter->second : nullptr;
	}

	auto PetMotionTable::Get() const -> const std::vector<PetMotion>&
	{
		return _vector;
	}
}

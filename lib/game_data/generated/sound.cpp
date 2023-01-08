/**********************************************************
         AUTO GENERATED FILE BY sox_code_generator
                   DO NOT EDIT THIS FILE
**********************************************************/
#include "sound.h"

#include "lib/common/stream/stream_reader.h"
#include "lib/game_base/data/sox/sox_file.h"
#include "lib/game_data/game_data_registry.h"

namespace cebreiro::gamedata
{
	[[maybe_unused]]
	static GameDataRegistry<SoundTable> registry;

	Sound::Sound(StreamReader& reader)
	{
		index = reader.ReadInt32();
		soundKey1Time = reader.ReadInt32();
		soundKey1Wav = reader.ReadInt32();
		soundKey2Time = reader.ReadInt32();
		soundKey2Wav = reader.ReadInt32();
		soundKey3Time = reader.ReadInt32();
		soundKey3Wav = reader.ReadInt32();
		soundKey4Time = reader.ReadInt32();
		soundKey4Wav = reader.ReadInt32();
		soundKey5Time = reader.ReadInt32();
		soundKey5Wav = reader.ReadInt32();
		soundKey6Time = reader.ReadInt32();
		soundKey6Wav = reader.ReadInt32();
		soundKey7Time = reader.ReadInt32();
		soundKey7Wav = reader.ReadInt32();
		soundKey8Time = reader.ReadInt32();
		soundKey8Wav = reader.ReadInt32();
	}

	void SoundTable::LoadFromFile(const std::filesystem::path& path)
	{
		gamebase::SoxFile fileData(path / "sound.sox");
		StreamReader reader(fileData.gameData.data(), fileData.gameData.size());

		_vector.reserve(fileData.rowCount);
		for (int32_t i = 0; i < fileData.rowCount; ++i)
		{
			_vector.emplace_back(reader);
		}

		for (const Sound& data : _vector)
		{
			_umap[data.index] = &data;
		}
	}

	auto SoundTable::Find(int32_t index) const -> const Sound*
	{
		auto iter = _umap.find(index);
		return iter != _umap.end() ? iter->second : nullptr;
	}

	auto SoundTable::Get() const -> const std::vector<Sound>&
	{
		return _vector;
	}
}
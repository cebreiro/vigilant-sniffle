/**********************************************************
         AUTO GENERATED FILE BY sox_code_generator
                   DO NOT EDIT THIS FILE
**********************************************************/
#include "emotion_list.h"

#include "lib/common/stream/stream_reader.h"
#include "lib/game_base/data/sox/sox_file.h"
#include "lib/game_data/game_data_registry.h"

namespace cebreiro::gamedata
{
	[[maybe_unused]]
	static GameDataRegistry<EmotionListTable> registry;

	EmotionList::EmotionList(StreamReader& reader)
	{
		index = reader.ReadInt32();
		name = reader.ReadString(reader.ReadUInt16());
		group = reader.ReadInt32();
		mmotionId = reader.ReadInt32();
		fmotionId = reader.ReadInt32();
		mfxId = reader.ReadInt32();
		ffxId = reader.ReadInt32();
		page = reader.ReadInt32();
		levelRequire = reader.ReadInt32();
		itemRequire = reader.ReadInt32();
		itemConsume = reader.ReadInt32();
		emotionIndicate = reader.ReadInt32();
	}

	void EmotionListTable::LoadFromFile(const std::filesystem::path& path)
	{
		gamebase::SoxFile fileData(path / "EMOTION_LIST.sox");
		StreamReader reader(fileData.gameData.data(), fileData.gameData.size());

		_vector.reserve(fileData.rowCount);
		for (int32_t i = 0; i < fileData.rowCount; ++i)
		{
			_vector.emplace_back(reader);
		}

		for (const EmotionList& data : _vector)
		{
			_umap[data.index] = &data;
		}
	}

	auto EmotionListTable::Find(int32_t index) const -> const EmotionList*
	{
		auto iter = _umap.find(index);
		return iter != _umap.end() ? iter->second : nullptr;
	}

	auto EmotionListTable::Get() const -> const std::vector<EmotionList>&
	{
		return _vector;
	}
}

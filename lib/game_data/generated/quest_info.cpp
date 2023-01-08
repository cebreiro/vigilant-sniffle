/**********************************************************
         AUTO GENERATED FILE BY sox_code_generator
                   DO NOT EDIT THIS FILE
**********************************************************/
#include "quest_info.h"

#include "lib/common/stream/stream_reader.h"
#include "lib/game_base/data/sox/sox_file.h"
#include "lib/game_data/game_data_registry.h"

namespace cebreiro::gamedata
{
	[[maybe_unused]]
	static GameDataRegistry<QuestInfoTable> registry;

	QuestInfo::QuestInfo(StreamReader& reader)
	{
		index = reader.ReadInt32();
		descFuncId = reader.ReadInt32();
		questCancelable = reader.ReadInt32();
	}

	void QuestInfoTable::LoadFromFile(const std::filesystem::path& path)
	{
		gamebase::SoxFile fileData(path / "QuestInfo.sox");
		StreamReader reader(fileData.gameData.data(), fileData.gameData.size());

		_vector.reserve(fileData.rowCount);
		for (int32_t i = 0; i < fileData.rowCount; ++i)
		{
			_vector.emplace_back(reader);
		}

		for (const QuestInfo& data : _vector)
		{
			_umap[data.index] = &data;
		}
	}

	auto QuestInfoTable::Find(int32_t index) const -> const QuestInfo*
	{
		auto iter = _umap.find(index);
		return iter != _umap.end() ? iter->second : nullptr;
	}

	auto QuestInfoTable::Get() const -> const std::vector<QuestInfo>&
	{
		return _vector;
	}
}
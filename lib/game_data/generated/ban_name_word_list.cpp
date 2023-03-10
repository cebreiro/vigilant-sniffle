/**********************************************************
         AUTO GENERATED FILE BY sox_code_generator
                   DO NOT EDIT THIS FILE
**********************************************************/
#include "ban_name_word_list.h"

#include "lib/common/stream/stream_reader.h"
#include "lib/game_base/data/sox/sox_file.h"
#include "lib/game_data/game_data_registry.h"

namespace cebreiro::gamedata
{
	[[maybe_unused]]
	static GameDataRegistry<BanNameWordListTable> registry;

	BanNameWordList::BanNameWordList(StreamReader& reader)
	{
		index = reader.ReadInt32();
		banStr = reader.ReadString(reader.ReadUInt16());
		banType = reader.ReadInt32();
	}

	void BanNameWordListTable::LoadFromFile(const std::filesystem::path& path)
	{
		gamebase::SoxFile fileData(path / "BAN_NAME_WORD_LIST.sox");
		StreamReader reader(fileData.gameData.data(), fileData.gameData.size());

		_vector.reserve(fileData.rowCount);
		for (int32_t i = 0; i < fileData.rowCount; ++i)
		{
			_vector.emplace_back(reader);
		}

		for (const BanNameWordList& data : _vector)
		{
			_umap[data.index] = &data;
		}
	}

	auto BanNameWordListTable::Find(int32_t index) const -> const BanNameWordList*
	{
		auto iter = _umap.find(index);
		return iter != _umap.end() ? iter->second : nullptr;
	}

	auto BanNameWordListTable::Get() const -> const std::vector<BanNameWordList>&
	{
		return _vector;
	}
}

/**********************************************************
         AUTO GENERATED FILE BY sox_code_generator
                   DO NOT EDIT THIS FILE
**********************************************************/
#include "minigame_typing_word.h"

#include "lib/common/stream/stream_reader.h"
#include "lib/game_base/data/sox/sox_file.h"
#include "lib/game_data/game_data_registry.h"

namespace cebreiro::gamedata
{
	[[maybe_unused]]
	static GameDataRegistry<MinigameTypingWordTable> registry;

	MinigameTypingWord::MinigameTypingWord(StreamReader& reader)
	{
		index = reader.ReadInt32();
		typingWord = reader.ReadString(reader.ReadUInt16());
	}

	void MinigameTypingWordTable::LoadFromFile(const std::filesystem::path& path)
	{
		gamebase::SoxFile fileData(path / "MINIGAME_TYPING_WORD.sox");
		StreamReader reader(fileData.gameData.data(), fileData.gameData.size());

		_vector.reserve(fileData.rowCount);
		for (int32_t i = 0; i < fileData.rowCount; ++i)
		{
			_vector.emplace_back(reader);
		}

		for (const MinigameTypingWord& data : _vector)
		{
			_umap[data.index] = &data;
		}
	}

	auto MinigameTypingWordTable::Find(int32_t index) const -> const MinigameTypingWord*
	{
		auto iter = _umap.find(index);
		return iter != _umap.end() ? iter->second : nullptr;
	}

	auto MinigameTypingWordTable::Get() const -> const std::vector<MinigameTypingWord>&
	{
		return _vector;
	}
}

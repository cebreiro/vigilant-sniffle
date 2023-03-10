/**********************************************************
         AUTO GENERATED FILE BY sox_code_generator
                   DO NOT EDIT THIS FILE
**********************************************************/
#include "minigame_typing.h"

#include "lib/common/stream/stream_reader.h"
#include "lib/game_base/data/sox/sox_file.h"
#include "lib/game_data/game_data_registry.h"

namespace cebreiro::gamedata
{
	[[maybe_unused]]
	static GameDataRegistry<MinigameTypingTable> registry;

	MinigameTyping::MinigameTyping(StreamReader& reader)
	{
		index = reader.ReadInt32();
		monsterId = reader.ReadInt32();
		monsterName = reader.ReadString(reader.ReadUInt16());
		monsterModelId = reader.ReadInt32();
		monsterSpeed = reader.ReadInt32();
		monsterAdd = reader.ReadInt32();
		minWordLength = reader.ReadInt32();
		maxWordLength = reader.ReadInt32();
	}

	void MinigameTypingTable::LoadFromFile(const std::filesystem::path& path)
	{
		gamebase::SoxFile fileData(path / "MINIGAME_TYPING.sox");
		StreamReader reader(fileData.gameData.data(), fileData.gameData.size());

		_vector.reserve(fileData.rowCount);
		for (int32_t i = 0; i < fileData.rowCount; ++i)
		{
			_vector.emplace_back(reader);
		}

		for (const MinigameTyping& data : _vector)
		{
			_umap[data.index] = &data;
		}
	}

	auto MinigameTypingTable::Find(int32_t index) const -> const MinigameTyping*
	{
		auto iter = _umap.find(index);
		return iter != _umap.end() ? iter->second : nullptr;
	}

	auto MinigameTypingTable::Get() const -> const std::vector<MinigameTyping>&
	{
		return _vector;
	}
}

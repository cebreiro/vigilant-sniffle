/**********************************************************
         AUTO GENERATED FILE BY sox_code_generator
                   DO NOT EDIT THIS FILE
**********************************************************/
#pragma once
#include <cstdint>
#include <string>
#include <vector>
#include <unordered_map>
#include <filesystem>
#include "lib/game_data/game_data_table.h"

namespace cebreiro { class StreamReader; }

namespace cebreiro::gamedata
{
	struct MinigameTyping
	{
		MinigameTyping() = default;
		explicit MinigameTyping(StreamReader& reader);

		int32_t index = 0;
		int32_t monsterId = 0;
		std::string monsterName;
		int32_t monsterModelId = 0;
		int32_t monsterSpeed = 0;
		int32_t monsterAdd = 0;
		int32_t minWordLength = 0;
		int32_t maxWordLength = 0;
	};

	class MinigameTypingTable : public GameDataTable
	{
	public:
		 static constexpr int64_t INDEX = 47;

	public:
		void LoadFromFile(const std::filesystem::path& path);

		auto Find(int32_t index) const -> const MinigameTyping*;
		auto Get() const -> const std::vector<MinigameTyping>&;

	private:
		std::vector<MinigameTyping> _vector;
		std::unordered_map<int32_t, const MinigameTyping*> _umap;
	};
}
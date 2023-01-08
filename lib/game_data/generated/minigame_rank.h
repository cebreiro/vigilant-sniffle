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
	struct MinigameRank
	{
		MinigameRank() = default;
		explicit MinigameRank(StreamReader& reader);

		int32_t index = 0;
		std::string rankValue;
		std::string rankDesc;
	};

	class MinigameRankTable : public GameDataTable
	{
	public:
		 static constexpr int64_t INDEX = 45;

	public:
		void LoadFromFile(const std::filesystem::path& path);

		auto Find(int32_t index) const -> const MinigameRank*;
		auto Get() const -> const std::vector<MinigameRank>&;

	private:
		std::vector<MinigameRank> _vector;
		std::unordered_map<int32_t, const MinigameRank*> _umap;
	};
}
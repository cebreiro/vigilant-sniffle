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
	struct BanNameWordList
	{
		BanNameWordList() = default;
		explicit BanNameWordList(StreamReader& reader);

		int32_t index = 0;
		std::string banStr;
		int32_t banType = 0;
	};

	class BanNameWordListTable : public GameDataTable
	{
	public:
		 static constexpr int64_t INDEX = 3;

	public:
		void LoadFromFile(const std::filesystem::path& path);

		auto Find(int32_t index) const -> const BanNameWordList*;
		auto Get() const -> const std::vector<BanNameWordList>&;

	private:
		std::vector<BanNameWordList> _vector;
		std::unordered_map<int32_t, const BanNameWordList*> _umap;
	};
}

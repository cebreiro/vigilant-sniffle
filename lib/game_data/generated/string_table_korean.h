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
	struct StringTableKorean
	{
		StringTableKorean() = default;
		explicit StringTableKorean(StreamReader& reader);

		int32_t index = 0;
		std::string string;
		std::string desc;
	};

	class StringTableKoreanTable : public GameDataTable
	{
	public:
		 static constexpr int64_t INDEX = 77;

	public:
		void LoadFromFile(const std::filesystem::path& path);

		auto Find(int32_t index) const -> const StringTableKorean*;
		auto Get() const -> const std::vector<StringTableKorean>&;

	private:
		std::vector<StringTableKorean> _vector;
		std::unordered_map<int32_t, const StringTableKorean*> _umap;
	};
}

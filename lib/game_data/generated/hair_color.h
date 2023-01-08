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
	struct HairColor
	{
		HairColor() = default;
		explicit HairColor(StreamReader& reader);

		int32_t index = 0;
		int32_t pnxValue = 0;
		int32_t r = 0;
		int32_t g = 0;
		int32_t b = 0;
	};

	class HairColorTable : public GameDataTable
	{
	public:
		 static constexpr int64_t INDEX = 15;

	public:
		void LoadFromFile(const std::filesystem::path& path);

		auto Find(int32_t index) const -> const HairColor*;
		auto Get() const -> const std::vector<HairColor>&;

	private:
		std::vector<HairColor> _vector;
		std::unordered_map<int32_t, const HairColor*> _umap;
	};
}

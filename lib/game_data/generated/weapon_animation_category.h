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
	struct WeaponAnimationCategory
	{
		WeaponAnimationCategory() = default;
		explicit WeaponAnimationCategory(StreamReader& reader);

		int32_t index = 0;
		int32_t _default = 0;
		int32_t walk = 0;
		int32_t run = 0;
		int32_t idle = 0;
		int32_t disarm = 0;
		int32_t rearm = 0;
		int32_t attacka = 0;
		int32_t attackb = 0;
		int32_t attackc = 0;
		int32_t attackd = 0;
		int32_t reload = 0;
		int32_t attackaTime = 0;
		int32_t attackbTime = 0;
		int32_t attackcTime = 0;
		int32_t attackdTime = 0;
	};

	class WeaponAnimationCategoryTable : public GameDataTable
	{
	public:
		 static constexpr int64_t INDEX = 82;

	public:
		void LoadFromFile(const std::filesystem::path& path);

		auto Find(int32_t index) const -> const WeaponAnimationCategory*;
		auto Get() const -> const std::vector<WeaponAnimationCategory>&;

	private:
		std::vector<WeaponAnimationCategory> _vector;
		std::unordered_map<int32_t, const WeaponAnimationCategory*> _umap;
	};
}
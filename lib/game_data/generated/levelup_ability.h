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
	struct LevelupAbility
	{
		LevelupAbility() = default;
		explicit LevelupAbility(StreamReader& reader);

		int32_t index = 0;
		int32_t w1Ability = 0;
		int32_t w1Quest = 0;
		std::string w1Title;
		int32_t w2Ability = 0;
		int32_t w2Quest = 0;
		std::string w2Title;
		int32_t w3Ability = 0;
		int32_t w3Quest = 0;
		std::string w3Title;
		int32_t c1Ability = 0;
		int32_t c1Quest = 0;
		std::string c1Title;
		int32_t c2Ability = 0;
		int32_t c2Quest = 0;
		std::string c2Title;
		int32_t c3Ability = 0;
		int32_t c3Quest = 0;
		std::string c3Title;
		int32_t d1Ability = 0;
		int32_t d1Quest = 0;
		std::string d1Title;
		int32_t d2Ability = 0;
		int32_t d2Quest = 0;
		std::string d2Title;
		int32_t d3Ability = 0;
		int32_t d3Quest = 0;
		std::string d3Title;
		int32_t e1Ability = 0;
		int32_t e1Quest = 0;
		std::string e1Title;
		int32_t e2Ability = 0;
		int32_t e2Quest = 0;
		std::string e2Title;
		int32_t e3Ability = 0;
		int32_t e3Quest = 0;
		std::string e3Title;
		int32_t a1Ability = 0;
		int32_t a1Quest = 0;
		std::string a1Title;
		int32_t a2Ability = 0;
		int32_t a2Quest = 0;
		std::string a2Title;
		int32_t a3Ability = 0;
		int32_t a3Quest = 0;
		std::string a3Title;
	};

	class LevelupAbilityTable : public GameDataTable
	{
	public:
		 static constexpr int64_t INDEX = 36;

	public:
		void LoadFromFile(const std::filesystem::path& path);

		auto Find(int32_t index) const -> const LevelupAbility*;
		auto Get() const -> const std::vector<LevelupAbility>&;

	private:
		std::vector<LevelupAbility> _vector;
		std::unordered_map<int32_t, const LevelupAbility*> _umap;
	};
}

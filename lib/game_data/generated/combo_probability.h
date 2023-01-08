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
	struct ComboProbability
	{
		ComboProbability() = default;
		explicit ComboProbability(StreamReader& reader);

		int32_t index = 0;
		float enableCombo2 = 0.f;
		float enableCombo3 = 0.f;
		float enableCombo4 = 0.f;
		float enableCombo5 = 0.f;
		float enableCombo6 = 0.f;
		float enableCombo7 = 0.f;
		float enableCombo8 = 0.f;
		float enableCombo9 = 0.f;
		float enableCombo10 = 0.f;
	};

	class ComboProbabilityTable : public GameDataTable
	{
	public:
		 static constexpr int64_t INDEX = 5;

	public:
		void LoadFromFile(const std::filesystem::path& path);

		auto Find(int32_t index) const -> const ComboProbability*;
		auto Get() const -> const std::vector<ComboProbability>&;

	private:
		std::vector<ComboProbability> _vector;
		std::unordered_map<int32_t, const ComboProbability*> _umap;
	};
}
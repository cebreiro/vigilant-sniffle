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
	struct SkillInt
	{
		SkillInt() = default;
		explicit SkillInt(StreamReader& reader);

		int32_t index = 0;
		std::string description;
		int32_t textureid = 0;
		int32_t count = 0;
	};

	class SkillIntTable : public GameDataTable
	{
	public:
		 static constexpr int64_t INDEX = 75;

	public:
		void LoadFromFile(const std::filesystem::path& path);

		auto Find(int32_t index) const -> const SkillInt*;
		auto Get() const -> const std::vector<SkillInt>&;

	private:
		std::vector<SkillInt> _vector;
		std::unordered_map<int32_t, const SkillInt*> _umap;
	};
}

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
	struct Prop
	{
		Prop() = default;
		explicit Prop(StreamReader& reader);

		int32_t index = 0;
		std::string name;
		int32_t playerActionCategory = 0;
		int32_t minRange = 0;
		int32_t posX = 0;
		int32_t posY = 0;
		int32_t posZ = 0;
	};

	class PropTable : public GameDataTable
	{
	public:
		 static constexpr int64_t INDEX = 66;

	public:
		void LoadFromFile(const std::filesystem::path& path);

		auto Find(int32_t index) const -> const Prop*;
		auto Get() const -> const std::vector<Prop>&;

	private:
		std::vector<Prop> _vector;
		std::unordered_map<int32_t, const Prop*> _umap;
	};
}

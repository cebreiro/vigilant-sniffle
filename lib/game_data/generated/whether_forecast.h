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
	struct WhetherForecast
	{
		WhetherForecast() = default;
		explicit WhetherForecast(StreamReader& reader);

		int32_t index = 0;
		int32_t whetherType = 0;
		int32_t lightType = 0;
		int32_t density = 0;
		int32_t cloudType = 0;
		int32_t fog = 0;
		float fogRate = 0.f;
		int32_t fogColorR = 0;
		int32_t fogColorG = 0;
		int32_t fogColorB = 0;
		int32_t cloudA = 0;
		int32_t cloudB = 0;
	};

	class WhetherForecastTable : public GameDataTable
	{
	public:
		 static constexpr int64_t INDEX = 84;

	public:
		void LoadFromFile(const std::filesystem::path& path);

		auto Find(int32_t index) const -> const WhetherForecast*;
		auto Get() const -> const std::vector<WhetherForecast>&;

	private:
		std::vector<WhetherForecast> _vector;
		std::unordered_map<int32_t, const WhetherForecast*> _umap;
	};
}

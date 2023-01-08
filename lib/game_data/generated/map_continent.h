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
	struct MapContinent
	{
		MapContinent() = default;
		explicit MapContinent(StreamReader& reader);

		int32_t index = 0;
		int32_t continentId = 0;
		int32_t zoneId = 0;
		int32_t zoneX1 = 0;
		int32_t zoneY1 = 0;
		int32_t zoneX2 = 0;
		int32_t zoneY2 = 0;
		int32_t zoneNameX1 = 0;
		int32_t zoneNameY1 = 0;
		int32_t link01X1 = 0;
		int32_t link01Y1 = 0;
		int32_t link02X1 = 0;
		int32_t link02Y1 = 0;
		int32_t link03X1 = 0;
		int32_t link03Y1 = 0;
		int32_t link04X1 = 0;
		int32_t link04Y1 = 0;
		int32_t link05X1 = 0;
		int32_t link05Y1 = 0;
		int32_t link06X1 = 0;
		int32_t link06Y1 = 0;
		int32_t dungeon01String = 0;
		int32_t dungeon01X1 = 0;
		int32_t dungeon01Y1 = 0;
		int32_t dungeon02String = 0;
		int32_t dungeon02X1 = 0;
		int32_t dungeon02Y1 = 0;
		int32_t dungeon03String = 0;
		int32_t dungeon03X1 = 0;
		int32_t dungeon03Y1 = 0;
		int32_t dungeon04String = 0;
		int32_t dungeon04X1 = 0;
		int32_t dungeon04Y1 = 0;
		int32_t dungeon05String = 0;
		int32_t dungeon05X1 = 0;
		int32_t dungeon05Y1 = 0;
	};

	class MapContinentTable : public GameDataTable
	{
	public:
		 static constexpr int64_t INDEX = 41;

	public:
		void LoadFromFile(const std::filesystem::path& path);

		auto Find(int32_t index) const -> const MapContinent*;
		auto Get() const -> const std::vector<MapContinent>&;

	private:
		std::vector<MapContinent> _vector;
		std::unordered_map<int32_t, const MapContinent*> _umap;
	};
}

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
	struct ItemClothes
	{
		ItemClothes() = default;
		explicit ItemClothes(StreamReader& reader);

		int32_t index = 0;
		std::string name;
		int32_t generate = 0;
		std::string explanation;
		int32_t invenWidth = 0;
		int32_t invenHeight = 0;
		int32_t maxOverlapCount = 0;
		int32_t rarity = 0;
		int32_t price = 0;
		int32_t modelID = 0;
		int32_t modelColor = 0;
		int32_t dropSound = 0;
		int32_t useQuickSlot = 0;
		int32_t oneMoreItem = 0;
		int32_t equipPos = 0;
		int32_t armorClass = 0;
		int32_t defense = 0;
		int32_t protection = 0;
		int32_t equipEffect1 = 0;
		int32_t equipEffectValue1 = 0;
		int32_t equipEffect2 = 0;
		int32_t equipEffectValue2 = 0;
		int32_t equipEffect3 = 0;
		int32_t equipEffectValue3 = 0;
		int32_t equipEffect4 = 0;
		int32_t equipEffectValue4 = 0;
		int32_t constraint1 = 0;
		int32_t constraint2 = 0;
		int32_t constraint3 = 0;
		int32_t constraint4 = 0;
		int32_t constraint5 = 0;
		int32_t constraint6 = 0;
		int32_t constraint7 = 0;
		int32_t constraint8 = 0;
		int32_t constraintValue1 = 0;
		int32_t constraintValue2 = 0;
		int32_t constraintValue3 = 0;
		int32_t constraintValue4 = 0;
		int32_t constraintValue5 = 0;
		int32_t constraintValue6 = 0;
		int32_t constraintValue7 = 0;
		int32_t constraintValue8 = 0;
		int32_t constraintOR1 = 0;
		int32_t constraintOR2 = 0;
		int32_t constraintOR3 = 0;
		int32_t constraintOR4 = 0;
		int32_t constraintOR5 = 0;
		int32_t constraintOR6 = 0;
		int32_t constraintOR7 = 0;
		int32_t ableToSell = 0;
		int32_t ableToTrade = 0;
		int32_t ableToDrop = 0;
		int32_t ableToDestroy = 0;
		int32_t ableToStorage = 0;
	};

	class ItemClothesTable : public GameDataTable
	{
	public:
		 static constexpr int64_t INDEX = 27;

	public:
		void LoadFromFile(const std::filesystem::path& path);

		auto Find(int32_t index) const -> const ItemClothes*;
		auto Get() const -> const std::vector<ItemClothes>&;

	private:
		std::vector<ItemClothes> _vector;
		std::unordered_map<int32_t, const ItemClothes*> _umap;
	};
}

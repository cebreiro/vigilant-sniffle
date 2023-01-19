#pragma once
#include <cstdint>
#include <unordered_map>
#include "lib/game_data/game_data_table.h"

namespace cebreiro::gamedata
{
	enum class ItemDataType
	{
		Weapon,
		Clothes,
		Edible,
		Etc,
		PetFood,
	};

	struct ItemCommon
	{
		ItemDataType type = ItemDataType::Weapon;
		int32_t index = 0;
		int32_t width = 0;
		int32_t height = 0;
		int32_t maxOverlapCount = 0;
		int32_t rarity = 0;
		int32_t price = 0;
		int32_t modelID = 0;
		int32_t modelColor = 0;
		int32_t useQuickSlot = 0;
		int32_t oneMoreItem = 0;
		int32_t ableToSell = 0;
		int32_t ableToTrade = 0;
		int32_t ableToDrop = 0;
		int32_t ableToDestroy = 0;
		int32_t ableToStorage = 0;
	};

	class ItemCommonRefinedTable : public GameDataRefinedTable
	{
	public:
		void LoadFromSource(GameDataSource& source);

		auto Find(int32_t index) const -> const ItemCommon*;

	private:
		std::unordered_map<int32_t, ItemCommon> _items;
	};
}
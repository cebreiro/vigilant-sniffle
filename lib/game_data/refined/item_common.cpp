#include "item_common.h"

#include "lib/game_data/game_data_registry.h"
#include "lib/game_data/generated/item_weapon.h"
#include "lib/game_data/generated/item_clothes.h"
#include "lib/game_data/generated/item_edible.h"
#include "lib/game_data/generated/item_etc.h"
#include "lib/game_data/generated/item_pet_food.h"

namespace cebreiro::gamedata
{
	[[maybe_unused]]
	static GameRefinedDataRegistry<ItemCommonRefinedTable> registry;

	void ItemCommonRefinedTable::LoadFromSource(GameDataSource& source)
	{
		auto addCommonData = [this]<typename T>(const std::shared_ptr<T>&table)
		{
			ItemDataType type = ItemDataType::Weapon;

			if constexpr (std::is_same_v<T, ItemWeaponTable>)
			{
				type = ItemDataType::Weapon;
			}
			else if constexpr (std::is_same_v<T, ItemClothesTable>)
			{
				type = ItemDataType::Clothes;
			}
			else if constexpr (std::is_same_v<T, ItemEdibleTable>)
			{
				type = ItemDataType::Edible;
			}
			else if constexpr (std::is_same_v<T, ItemEtcTable>)
			{
				type = ItemDataType::Etc;
			}
			else if constexpr (std::is_same_v<T, ItemPetFoodTable>)
			{
				type = ItemDataType::PetFood;
			}
			else
			{
				static_assert(!sizeof(T), "not implemented");
			}

			for (const auto& data : table->Get())
			{
				[[maybe_unused]] bool inserted = _items.try_emplace(data.index, ItemCommon{
					.type = type,
					.index = data.index,
					.width = data.invenWidth,
					.height = data.invenHeight,
					.maxOverlapCount = data.maxOverlapCount,
					.rarity = data.rarity,
					.price = data.price,
					.modelID = data.modelID,
					.modelColor = data.modelColor,
					.useQuickSlot = data.useQuickSlot,
					.oneMoreItem = data.oneMoreItem,
					.ableToSell = data.ableToSell,
					.ableToTrade = data.ableToTrade,
					.ableToDrop = data.ableToDrop,
					.ableToDestroy = data.ableToDestroy,
					.ableToStorage = data.ableToStorage,
					}).second;
				assert(inserted);
			}
		};

		addCommonData(source.Get<ItemWeaponTable>());
		addCommonData(source.Get<ItemClothesTable>());
		addCommonData(source.Get<ItemEdibleTable>());
		addCommonData(source.Get<ItemEtcTable>());
		addCommonData(source.Get<ItemPetFoodTable>());
	}

	auto ItemCommonRefinedTable::Find(int32_t index) const -> const ItemCommon*
	{
		auto iter = _items.find(index);
		return iter != _items.end() ? &iter->second : nullptr;
	}
}

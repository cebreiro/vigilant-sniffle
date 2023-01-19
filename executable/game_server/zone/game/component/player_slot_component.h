#pragma once
#include "zone/game/component/component_base.h"
#include "zone/game/domain/slot/inventory.h"
#include "zone/game/object/game_object_id.h"

namespace cebreiro::gamebase
{
	struct CharacterItem;
}

namespace cebreiro::gamedata
{
	class ItemCommonRefinedTable;
}

namespace cebreiro::gamedb
{
	struct Character;
}

namespace cebreiro::zone
{
	class Item;
}

namespace cebreiro::zone
{
	class PlayerSlotComponent : public ComponentBase
	{
	public:
		PlayerSlotComponent(GameObject& object, const gamedb::Character& character);
		~PlayerSlotComponent();

	private:
		auto CreateItem(const gamebase::CharacterItem& item) const -> std::shared_ptr<Item>;

	private:
		std::shared_ptr<gamedata::ItemCommonRefinedTable> _itemDataTable;
		std::map<GameObjectId, std::shared_ptr<Item>> _items;
		std::unique_ptr<Inventory> _inventory;
		Item* _pickItem = nullptr;
	};
}
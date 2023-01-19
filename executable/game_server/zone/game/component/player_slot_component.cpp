#include "player_slot_component.h"

#include "lib/game_base/type/equip_position.h"
#include "lib/game_data/game_data_source.h"
#include "lib/game_data/refined/item_common.h"
#include "lib/game_db/entity/character.h"
#include "lib/game_service/service_locator_interface.h"
#include "zone/game/zone.h"
#include "zone/game/component/item_position_component.h"
#include "zone/game/object/game_object.h"
#include "zone/game/object/item.h"

namespace cebreiro::zone
{
	PlayerSlotComponent::PlayerSlotComponent(GameObject& object, const gamedb::Character& character)
		: ComponentBase(object)
		, _itemDataTable(_object.GetZone().GetServiceLocator().GameDataSource().Get<gamedata::ItemCommonRefinedTable>())
	{

		for (const gamebase::CharacterItem& item : character.items)
		{
			auto position = static_cast<type::EquipPosition>(item.equip_position);
			if (!IsValid(position))
			{
				continue;
			}

			auto itemObject = CreateItem(item);
			_items[itemObject->Id()] = itemObject;

			const auto& itemPosition = itemObject->Get<ItemPositionComponent>();

			if (itemPosition.IsEquipped())
			{
				
			}
			else if (itemPosition.IsInQuickSlot())
			{
				// TODO: implement here
			}
			else if (itemPosition.IsPicked())
			{
				_pickItem = itemObject.get();
			}
			else
			{
				// _inventory->Add()
			}
		}
	}

	PlayerSlotComponent::~PlayerSlotComponent()
	{
	}

	auto PlayerSlotComponent::CreateItem(const gamebase::CharacterItem& item) const -> std::shared_ptr<Item>
	{
		Zone& zone = _object.GetZone();

		const gamedata::ItemCommon* data = _itemDataTable->Find(item.item_id);
		if (!data)
		{
			return {};
		}

		auto itemObject = std::make_shared<Item>(
			zone, zone.CreateGameObjectId(type::Object::Item), *data);
		(void)itemObject->Add(std::make_shared<ItemPositionComponent>(*itemObject, item));

		return itemObject;
	}
}

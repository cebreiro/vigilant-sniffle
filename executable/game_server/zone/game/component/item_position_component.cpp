#include "item_position_component.h"

#include "lib/game_base/db/character.h"

namespace cebreiro::zone
{
	ItemPositionComponent::ItemPositionComponent(GameObject& object, const gamebase::CharacterItem& item)
		: ComponentBase(object)
		, _picked(item.is_pick)
		, _quickSlot(item.is_in_quick)
	{
	}

	bool ItemPositionComponent::IsEquipped() const
	{
		return _equipPosition != type::EquipPosition::None;
	}

	bool ItemPositionComponent::IsPicked() const
	{
		return _picked;
	}

	bool ItemPositionComponent::IsInQuickSlot() const
	{
		return _quickSlot;
	}

	void ItemPositionComponent::SetPosition(int32_t page, int32_t x, int32_t y)
	{
		_page = page;
		_x = x;
		_y = y;
	}

	void ItemPositionComponent::SetPicked(bool value)
	{
		_picked = value;
	}

	void ItemPositionComponent::SetQuickSlot(bool value)
	{
		_quickSlot = value;
	}

	void ItemPositionComponent::SetEquipPosition(type::EquipPosition type)
	{
		_equipPosition = type;
	}

	void ItemPositionComponent::Reset()
	{
		_picked = false;
		_quickSlot = false;
		_equipPosition = type::EquipPosition::None;
		_page = -1;
		_x = -1;
		_y = -1;
	}

	auto ItemPositionComponent::GetEquipPosition() const -> type::EquipPosition
	{
		return _equipPosition;
	}

	auto ItemPositionComponent::GetPage() const -> int32_t
	{
		return _page;
	}

	auto ItemPositionComponent::GetX() const -> int32_t
	{
		return _x;
	}

	auto ItemPositionComponent::GetY() const -> int32_t
	{
		return _y;
	}
}

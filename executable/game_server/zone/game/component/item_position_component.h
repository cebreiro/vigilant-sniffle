#pragma once
#include "lib/game_base/type/equip_position.h"
#include "zone/game/component/component_base.h"

namespace cebreiro::gamebase
{
	struct CharacterItem;
}

namespace cebreiro::zone
{
	class ItemPositionComponent : public ComponentBase
	{
	public:
		ItemPositionComponent(GameObject& object, const gamebase::CharacterItem& item);

		bool IsEquipped() const;
		bool IsPicked() const;
		bool IsInQuickSlot() const;

		void SetPosition(int32_t page, int32_t x, int32_t y);
		void SetPicked(bool value);
		void SetQuickSlot(bool value);
		void SetEquipPosition(type::EquipPosition type);

		void Reset();

		auto GetEquipPosition() const -> type::EquipPosition;
		auto GetPage() const -> int32_t;
		auto GetX() const -> int32_t;
		auto GetY() const -> int32_t;

	private:
		bool _picked = false;
		bool _quickSlot = false;
		type::EquipPosition _equipPosition = type::EquipPosition::None;
		int32_t _page = -1;
		int32_t _x = -1;
		int32_t _y = -1;
	};
}
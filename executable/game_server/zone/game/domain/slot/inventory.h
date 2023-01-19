#pragma once
#include "zone/game/domain/slot/slot_container.h"

namespace cebreiro::zone
{
	class Item;
}

namespace cebreiro::zone
{
	class Inventory
	{
	public:
		static constexpr int32_t MAX_WIDTH = 6;
		static constexpr int32_t MAX_HEIGHT = 9;
		static constexpr int32_t MAX_PAGE = 5;

		using SlotContainerType = SlotContainer<Item*, MAX_WIDTH, MAX_HEIGHT, MAX_PAGE>;
		using Position = SlotContainerType::Position;
		using Range = SlotContainerType::Range;

	public:
		auto FindEmptySpace(int32_t width, int32_t height) const -> Position;

		bool IsEmpty(const Range& range);

		bool Add(Item* item, const Position& position);
		bool Remove(Item* item);

	private:
		SlotContainerType _slotContainer;
	};
}
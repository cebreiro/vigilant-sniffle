#pragma once
#include <cstdint>
#include "lib/common/enum_class.h"

namespace cebreiro::type
{
	ENUM_CLASS(SoxEquipPosition, int32_t,
		(None, 0)
		(Hat, 1)
		(Jacket, 2)
		(Pants, 3)
		(Gloves, 4)
		(Shoes, 5)
		(Necklace, 6)
		(Ring, 7)
		(Weapon, 8)
		(Bullet, 9)
		(Count, 10)
	)

	ENUM_CLASS(EquipPosition, int32_t,
		(None, 0)
		(Hat, 1)
		(Jacket, 2)
		(Gloves, 3)
		(Pants, 4)
		(Shoes, 5)
		(Weapon1, 6)
		(Necklace, 7)
		(Ring1, 8)
		(Ring2, 9)
		(Dummy, 10)
		(Bullet, 11)
		(Weapon2, 12)
		(Count, 13)
	)
}

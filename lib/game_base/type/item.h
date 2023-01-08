#pragma once
#include <cstdint>
#include "lib/common/enum_class.h"

namespace cebreiro::type
{
	ENUM_CLASS(Item, int32_t,
		(None, 0)
		(Weapon, 1)
		(Clothes, 2)
		(Edible, 3)
		(Etc, 4)
		(Petfood, 5)
	)
}

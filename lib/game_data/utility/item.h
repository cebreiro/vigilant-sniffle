#pragma once
#include "lib/game_base/type/job.h"

namespace cebreiro::gamedata
{
	struct ItemClothes;
}

namespace cebreiro::gamedata
{
	bool IsWearable(const ItemClothes& item, type::Job job, int32_t level);
}
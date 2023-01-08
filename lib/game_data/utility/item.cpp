#include "item.h"

#include <cstdint>
#include <ranges>
#include <utility>
#include <boost/container/static_vector.hpp>

#include "lib/game_data/generated/item_clothes.h"

namespace cebreiro::gamedata
{
	bool IsWearable(const ItemClothes& item, type::Job job, int32_t level)
	{
		std::initializer_list<std::tuple<int32_t, int32_t, int32_t>> constraints = {
			{ item.constraint2, item.constraintValue2, item.constraintOR2 },
			{ item.constraint3, item.constraintValue3, item.constraintOR3 },
			{ item.constraint4, item.constraintValue4, item.constraintOR4 },
			{ item.constraint5, item.constraintValue5, item.constraintOR5 },
			{ item.constraint6, item.constraintValue6, item.constraintOR6 },
			{ item.constraint7, item.constraintValue7, item.constraintOR7 },
			{ item.constraint8, item.constraintValue8, false },
		};

		auto view = std::ranges::filter_view(constraints, [](const auto& tuple)
			{
				return std::get<0>(tuple) != 0;
			});

		for (auto [constraintJob, constraintLevel, orCondition] : view)
		{
			if (job == static_cast<type::Job>(constraintJob) && level >= constraintLevel)
			{
				return true;
			}

			if (orCondition)
			{
				continue;
			}

			return false;
		}

		return false;
	}
}

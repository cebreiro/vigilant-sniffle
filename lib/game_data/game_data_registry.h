#pragma once
#include "lib/game_data/game_data_source.h"

namespace cebreiro::gamedata
{
	template <typename T>
	struct GameDataRegistry
	{
		GameDataRegistry()
		{
			GameDataSource::AddFactory<T>();
		}
	};
}
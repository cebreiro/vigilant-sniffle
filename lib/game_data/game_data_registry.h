#pragma once
#include "lib/game_data/game_data_source.h"

namespace cebreiro::gamedata
{
	template <GameDataTableConcept T>
	struct GameDataRegistry
	{
		GameDataRegistry()
		{
			GameDataSource::AddFactory<T>();
		}
	};

	template <GameDataRefinedTableConcept T>
	struct GameRefinedDataRegistry
	{
		GameRefinedDataRegistry()
		{
			GameDataSource::AddRefinedTableFactory<T>();
		}
	};
}
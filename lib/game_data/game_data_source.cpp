#include "game_data_source.h"

namespace cebreiro::gamedata
{
	GameDataSource::GameDataSource(const std::filesystem::path& directory)
		: _directory(directory)
	{
	}

	void GameDataSource::Reload()
	{
		for (const auto& [id, factory] : GetFactories())
		{
			std::shared_ptr<GameDataTable> table = factory(_directory);
			auto [iter, insert] = _tables.emplace(id, table);
			if (!insert)
			{
				iter->second = std::move(table);
			}
		}

	}

	auto GameDataSource::GetFactories() -> factory_container_type&
	{
		static factory_container_type instance;
		return instance;
	}
}

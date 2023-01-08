#pragma once
#include <cstdint>
#include <cassert>
#include <concepts>
#include <filesystem>
#include <functional>
#include <tbb/concurrent_unordered_map.h>
#include "lib/game_data/game_data_table.h"

namespace cebreiro::gamedata
{
	template <typename T>
	class GameData
	{
	public:
		GameData() = default;
		explicit GameData(std::shared_ptr<T> data)
			: _data(std::move(data))
		{
		}

		auto operator->() const -> const T*
		{
			return _data.get();
		}

	private:
		std::shared_ptr<T> _data;
	};

	class GameDataSource
	{
	public:
		using value_type = std::shared_ptr<GameDataTable>;
		using factory_type = std::function<value_type(const std::filesystem::path&)>;
		using factory_container_type = tbb::concurrent_unordered_map<int64_t, factory_type>;

	public:
		explicit GameDataSource(const std::filesystem::path& directory);

		void Reload();

		template <std::derived_from<GameDataTable> T>
		auto Get() const -> GameData<T>;

		template <std::derived_from<GameDataTable> T>
		static void AddFactory();

	private:
		static auto GetFactories() -> factory_container_type&;

	private:
		std::filesystem::path _directory;
		tbb::concurrent_unordered_map<int64_t, std::atomic<std::shared_ptr<GameDataTable>>> _tables;
	};

	template <std::derived_from<GameDataTable> T>
	auto GameDataSource::Get() const -> GameData<T>
	{
		auto iter = _tables.find(T::INDEX);
		if (iter == _tables.end())
		{
			assert(false);
			return GameData<T>();
		}

		std::shared_ptr<T> data = std::static_pointer_cast<T>(iter->second.load());
		assert(data);

		return GameData<T>(std::move(data));

	}

	template <std::derived_from<GameDataTable> T>
	void GameDataSource::AddFactory()
	{
		GetFactories()[T::INDEX] = [](const std::filesystem::path& directory) -> std::shared_ptr<GameDataTable>
		{
			auto table = std::make_shared<T>();
			table->LoadFromFile(directory);

			return table;
		};
	}
}

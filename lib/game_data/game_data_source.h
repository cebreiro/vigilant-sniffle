#pragma once
#include <cstdint>
#include <cassert>
#include <map>
#include <filesystem>
#include <functional>
#include <tbb/concurrent_unordered_map.h>
#include "lib/common/class_id.h"
#include "lib/game_data/game_data_table.h"

namespace cebreiro::gamedata
{
	class GameDataSource
	{
	public:
		using value_type = std::shared_ptr<GameDataTable>;
		using factory_type = std::function<value_type(const std::filesystem::path&)>;
		using factory_container_type = std::map<int64_t, factory_type>;

		using refined_value_type = std::shared_ptr<GameDataRefinedTable>;
		using refined_factory_type = std::function<refined_value_type(GameDataSource&)>;
		using refiend_factory_container_type = std::map<int64_t, refined_factory_type>;

	public:
		explicit GameDataSource(const std::filesystem::path& directory);

		void Reload();

		template <GameDataTableConcept T>
		auto Get() const -> std::shared_ptr<T>;

		template <GameDataRefinedTableConcept T>
		auto Get() const -> std::shared_ptr<T>;

		template <GameDataTableConcept T>
		static void AddFactory();

		template <GameDataRefinedTableConcept T>
		static void AddRefinedTableFactory();

	private:
		static auto GetFactories() -> factory_container_type&;
		static auto GetRefinedFactories() -> refiend_factory_container_type&;

	private:
		std::filesystem::path _directory;
		tbb::concurrent_unordered_map<int64_t, std::atomic<std::shared_ptr<GameDataTable>>> _tables;
		tbb::concurrent_unordered_map<int64_t, std::atomic<std::shared_ptr<GameDataRefinedTable>>> _refinedTables;
	};

	template <GameDataTableConcept T>
	auto GameDataSource::Get() const -> std::shared_ptr<T>
	{
		auto iter = _tables.find(T::INDEX);
		if (iter == _tables.end())
		{
			assert(false);
			return std::shared_ptr<T>();
		}

		auto item = iter->second.load();
		assert(typeid(*item) == typeid(T));

		return std::static_pointer_cast<T>(item);

	}

	template <GameDataRefinedTableConcept T>
	auto GameDataSource::Get() const -> std::shared_ptr<T>
	{
		int64_t classId = ClassId<GameDataRefinedTable>::GetId<T>();

		auto iter = _refinedTables.find(classId);
		if (iter == _refinedTables.end())
		{
			assert(false);
			return std::shared_ptr<T>();
		}

		auto item = iter->second.load();
		assert(typeid(*item) == typeid(T));

		return std::static_pointer_cast<T>(item);
	}

	template <GameDataTableConcept T>
	void GameDataSource::AddFactory()
	{
		GetFactories()[T::INDEX] = [](const std::filesystem::path& directory) -> value_type
		{
			auto table = std::make_shared<T>();
			table->LoadFromFile(directory);

			return table;
		};
	}

	template <GameDataRefinedTableConcept T>
	void GameDataSource::AddRefinedTableFactory()
	{
		int64_t classId = ClassId<GameDataRefinedTable>::GetId<T>();
		GetRefinedFactories()[classId] = [](GameDataSource& source) -> refined_value_type
		{
			auto table = std::make_shared<T>();
			table->LoadFromSource(source);

			return table;
		};
	}
}

#pragma once
#include <cstdint>
#include <filesystem>
#include <concepts>

namespace cebreiro::gamedata
{
	class GameDataSource;
}

namespace cebreiro::gamedata
{
	class GameDataTable
	{
	public:
		virtual ~GameDataTable() {}
	};

	template <typename T>
	concept GameDataTableConcept = std::derived_from<T, GameDataTable>
	&& requires (T t, std::filesystem::path path)
	{
		{t.LoadFromFile(path)} -> std::same_as<void>;
	};

	class GameDataRefinedTable
	{
	public:
		virtual ~GameDataRefinedTable() {}
	};

	template <typename T>
	concept GameDataRefinedTableConcept = std::derived_from<T, GameDataRefinedTable>
	&& requires (T t, GameDataSource& source)
	{
		{t.LoadFromSource(source)} -> std::same_as<void>;
	};
}
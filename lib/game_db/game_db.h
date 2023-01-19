#pragma once
#include <string>
#include "lib/common/execution/future.h"
#include "lib/game_base/db/account.h"
#include "lib/game_db/entity/character.h"

namespace cebreiro
{
	class ILogService;
	class ThreadPool;
}

namespace cebreiro::odbc
{
	class DataSource;
	class Connection;
}

namespace cebreiro::gamedb
{
	class GameDB
	{
		struct Context;

	public:
		GameDB(ILogService& logService, ThreadPool& threadPool, std::shared_ptr<odbc::DataSource> dataSource);
		~GameDB();

		void Stop();

		auto DropAndCreateCharacterDB() -> Future<void>;

		auto FindAccount(std::string name) -> Future<std::optional<gamebase::Account>>;

		auto CheckCharacterNameUsable(std::string name) -> Future<bool>;
		auto CreateCharacter(Character character) -> Future<bool>;
		auto DeleteCharacter(int64_t cid) -> Future<bool>;
		auto GetCharacter(int64_t cid) -> Future<std::optional<Character>>;
		auto GetCharacters(int64_t aid) -> Future<std::vector<Character>>;

	private:
		auto Ping(Context& context) const -> Future<void>;

		auto GetNextContext() -> Context&;

	private:
		ILogService& _logService;
		ThreadPool& _threadPool;
		std::shared_ptr<odbc::DataSource> _dataSource;
		std::vector<std::unique_ptr<Context>> _contexts;
	};
}
#include "game_db.h"

#include <cassert>
#include <ranges>

#include "lib/common/stacktrace_exception.h"
#include "lib/common/log/log_macro.h"
#include "lib/common/execution/thread_pool.h"
#include "lib/common/execution/future_await.h"
#include "lib/common/execution/executor_await.h"
#include "lib/odbc/connection.h"
#include "lib/odbc/data_source.h"
#include "lib/game_db/generated/account_table.h"
#include "lib/game_db/generated/character_table.h"

namespace cebreiro::gamedb
{
	struct GameDB::Context
	{
		ThreadPool::Strand strand;
		std::shared_ptr<odbc::Connection> connection;
		bool cancel = false;
		Future<void> pingOperation;
	};

	GameDB::GameDB(ILogService& logService, ThreadPool& threadPool, std::shared_ptr<odbc::DataSource> dataSource)
		: _logService(logService)
		, _threadPool(threadPool)
		, _dataSource(std::move(dataSource))
	{
		_contexts.reserve(_threadPool.GetConcurrency());

		for (size_t i = 0; i < _threadPool.GetConcurrency(); ++i)
		{
			Context& context = *_contexts.emplace_back(new Context{
				.strand = _threadPool.MakeStrand(),
				.connection = _dataSource->MakeConnection(),
			});

			context.pingOperation = Ping(context);
		}
	}

	GameDB::~GameDB()
	{
		Stop();
	}

	void GameDB::Stop()
	{
		for (const std::unique_ptr<Context>& context : _contexts)
		{
			std::atomic_ref(context->cancel).store(true);
		}

		for (const std::unique_ptr<Context>& context : _contexts)
		{
			context->pingOperation.Get();
		}

		_contexts.clear();
	}

	auto GameDB::DropAndCreateCharacterDB() -> Future<void>
	{
		Context& context = GetNextContext();
		co_await context.strand;

		odbc::Connection& connection = *context.connection;
		connection.SetCommitMode(odbc::Connection::CommitMode::Manual);

		try
		{
			CharacterTable table(connection);
			CharacterStatTable statTable(connection);
			CharacterJobTable jobTable(connection);
			CharacterItemTable itemTable(connection);
			CharacterSkillTable skillTable(connection);

			connection.BeginTransaction();

			table.DropTable();
			statTable.DropTable();
			jobTable.DropTable();
			itemTable.DropTable();
			skillTable.DropTable();

			table.CreateTable();
			statTable.CreateTable();
			jobTable.CreateTable();
			itemTable.CreateTable();
			skillTable.CreateTable();

			connection.EndTransaction();
		}
		catch (const std::exception& e)
		{
			LOGE(_logService,
				std::format("fail to remove game_db. exception: {}", e.what()))

			connection.Rollback();
		}

		connection.SetCommitMode(odbc::Connection::CommitMode::Auto);
	}

	auto GameDB::FindAccount(std::string name) -> Future<std::optional<gamebase::Account>>
	{
		Context& context = GetNextContext();
		co_await context.strand;

		AccountTable table(*context.connection);
		co_return table.FindByACCOUNT(name);
	}

	auto GameDB::CheckCharacterNameUsable(std::string name) -> Future<bool>
	{
		Context& context = GetNextContext();
		co_await context.strand;

		CharacterTable table(*context.connection);

		co_return !table.FindByNAME(name).has_value();
	}

	auto GameDB::CreateCharacter(Character character) -> Future<bool>
	{
		Context& context = GetNextContext();
		co_await context.strand;

		odbc::Connection& connection = *context.connection;

		CharacterTable table(connection);
		CharacterStatTable statTable(connection);
		CharacterJobTable jobTable(connection);
		CharacterItemTable itemTable(connection);
		CharacterSkillTable skillTable(connection);

		connection.SetCommitMode(odbc::Connection::CommitMode::Manual);
		bool result = false;

		try
		{
			connection.BeginTransaction();

			table.Add(character.base);
			statTable.Add(character.stat);
			jobTable.Add(character.job);

			for (const gamebase::CharacterItem& item : character.items)
			{
				itemTable.Add(item);
			}

			for (const auto& skill : character.skills)
			{
				skillTable.Add(skill);
			}

			connection.EndTransaction();
			result = true;
		}
		catch (const std::exception& e)
		{
			connection.Rollback();

			LOGE(_logService,
				std::format("fail to create character. exception: {}", e.what()))
		}

		connection.SetCommitMode(odbc::Connection::CommitMode::Auto);

		co_return result;
	}

	auto GameDB::DeleteCharacter(int64_t cid) -> Future<bool>
	{
		Context& context = GetNextContext();
		co_await context.strand;

		odbc::Connection& connection = *context.connection;

		// db_code_generator -> pk -> dependency on delete cascade
		CharacterTable table(connection);

		// TODO: return size_t;
		table.RemoveByID(cid);

		co_return true;
	}

	auto GameDB::GetCharacters(int64_t aid) -> Future<std::vector<Character>>
	{
		Context& context = GetNextContext();
		co_await context.strand;

		odbc::Connection& connection = *context.connection;

		CharacterTable table(connection);
		CharacterStatTable statTable(connection);
		CharacterJobTable jobTable(connection);
		CharacterItemTable itemTable(connection);
		CharacterSkillTable skillTable(connection);

		auto range = table.FindByAID(aid) | std::ranges::views::transform([&](const gamebase::Character& base)
			{
				std::optional<gamebase::CharacterStat> stat = statTable.FindByCID(base.id);
				std::optional<gamebase::CharacterJob> job = jobTable.FindByCID(base.id);

				if (!stat.has_value())
				{
					throw StacktraceException(
						std::format("fail to find character stat. cid: {}", base.id));
				}

				return Character{
					.base = base,
					.stat = std::move(stat.value()),
					.job = std::move(job.value()),
					.items = itemTable.FindByCID(base.id),
					.skills = skillTable.FindByCID(base.id),
				};
			});

		co_return std::vector<Character>(range.begin(), range.end());
	}

	auto GameDB::Ping(Context& context) const -> Future<void>
	{
		co_await context.strand;

		while (true)
		{
			try
			{
				auto statement = context.connection->GetStatement();
				statement.Prepare("SELECT 1");
				statement.Execute();
			}
			catch (const std::exception& e)
			{
				LOGC(_logService,
					std::format("connection pool ping operation error. exception: {}", e.what()))
			}

			for (size_t i = 0; i < 12; ++i)
			{
				if (std::atomic_ref(context.cancel).load())
				{
					goto EXIT;
				}
				else
				{
					constexpr uint64_t delayMilliseconds = 5000;
					co_await Delay(delayMilliseconds).ConfigureAwait(context.strand);
				}
			}
		}

	EXIT:
		co_return;
	}

	auto GameDB::GetNextContext() -> Context&
	{
		static std::atomic<size_t> i = 0;

		return *_contexts[i.fetch_add(1) % _contexts.size()];
	}
}

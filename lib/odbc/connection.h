#pragma once
#include <string>
#include "lib/odbc/odbc_include.h"
#include "lib/odbc/statement.h"

namespace cebreiro::odbc
{
	class DataSource;

	class Connection
	{
		friend class Statement;

	public:
		enum class CommitMode
		{
			Auto = SQL_AUTOCOMMIT_ON,
			Manual = SQL_AUTOCOMMIT_OFF,
		};

	public:
		Connection() = default;
		Connection(Connection&& rhs) noexcept;
		Connection& operator=(Connection&& rhs) noexcept;

		Connection(const DataSource& dataSource,
			std::string dsn,
			std::string user,
			std::string password);
		Connection(const DataSource& dataSource,
			std::string connectionString);

		~Connection();

		void BeginTransaction();
		void EndTransaction();
		void Rollback();

		auto GetStatement() -> Statement;

		auto GetCommitMode() const -> CommitMode;
		void SetCommitMode(CommitMode commitMode);

	private:
		SQLHDBC _handle = nullptr;
		CommitMode _commitMode = CommitMode::Auto;
	};
}
#include "connection.h"

#include <cassert>

#include "lib/odbc/data_source.h"
#include "lib/odbc/detail/odbc_util.h"

namespace cebreiro::odbc
{
	constexpr SQLSMALLINT CON_HANDLE_TYPE = SQL_HANDLE_DBC;

	Connection::Connection(Connection&& rhs) noexcept
	{
		(void)operator=(std::move(rhs));
	}

	Connection& Connection::operator=(Connection&& rhs) noexcept
	{
		Connection::~Connection();

		_handle = rhs._handle;

		rhs._handle = nullptr;

		return *this;
	}

	Connection::Connection(const DataSource& dataSource, 
		std::string dsn, 
		std::string user,
		std::string password)
	{
		SQLRETURN result = ::SQLAllocHandle(CON_HANDLE_TYPE, dataSource._handle, &_handle);
		detail::ThrowIfFail(result, CON_HANDLE_TYPE, _handle);

		result = ::SQLConnectA(
			_handle,
			reinterpret_cast<SQLCHAR*>(dsn.data()),
			static_cast<SQLSMALLINT>(dsn.size()),
			reinterpret_cast<SQLCHAR*>(user.data()),
			static_cast<SQLSMALLINT>(user.size()),
			reinterpret_cast<SQLCHAR*>(password.data()),
			static_cast<SQLSMALLINT>(password.size())
		);
		detail::ThrowIfFail(result, CON_HANDLE_TYPE, _handle);
	}

	Connection::Connection(const DataSource& dataSource, std::string connectionString)
	{
		SQLRETURN result = ::SQLAllocHandle(CON_HANDLE_TYPE, dataSource._handle, &_handle);
		detail::ThrowIfFail(result, CON_HANDLE_TYPE, _handle);

		constexpr SQLSMALLINT outConStringMax = 512;
		SQLCHAR outConString[outConStringMax] = {};
		SQLSMALLINT outConStringLength = 0;

		result = ::SQLDriverConnectA(
			_handle,
			nullptr,
			(SQLCHAR*)connectionString.data(),
			(SQLSMALLINT)connectionString.size(),
			outConString,
			outConStringMax,
			&outConStringLength,
			SQL_DRIVER_PROMPT
		);
		detail::ThrowIfFail(result, CON_HANDLE_TYPE, _handle);
	}

	Connection::~Connection()
	{
		if (_handle)
		{
			[[maybe_unused]] SQLRETURN result = ::SQLDisconnect(_handle);
			result = ::SQLFreeHandle(CON_HANDLE_TYPE, _handle);

			assert(detail::IsSuccess(result));
		}
	}

	void Connection::BeginTransaction()
	{
		SetCommitMode(CommitMode::Manual);
	}

	void Connection::EndTransaction()
	{
		SQLRETURN result = ::SQLEndTran(CON_HANDLE_TYPE, _handle, SQL_COMMIT);
		detail::ThrowIfFail(result, CON_HANDLE_TYPE, _handle);
	}

	void Connection::Rollback()
	{
		SQLRETURN result = ::SQLEndTran(CON_HANDLE_TYPE, _handle, SQL_ROLLBACK);
		detail::ThrowIfFail(result, CON_HANDLE_TYPE, _handle);
	}

	auto Connection::GetStatement() -> Statement
	{
		return Statement(*this);
	}

	auto Connection::GetCommitMode() const -> CommitMode
	{
		return _commitMode;
	}

	void Connection::SetCommitMode(CommitMode commitMode)
	{
		if (_commitMode != commitMode)
		{
			SQLRETURN result = ::SQLSetConnectAttr(
				_handle,
				SQL_ATTR_AUTOCOMMIT,
				reinterpret_cast<SQLPOINTER>(commitMode),
				SQL_IS_INTEGER);
			detail::ThrowIfFail(result, CON_HANDLE_TYPE, _handle);

			_commitMode = commitMode;
		}
	}
}

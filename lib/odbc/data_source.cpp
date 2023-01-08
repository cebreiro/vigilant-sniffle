#include "data_source.h"

#include <cassert>

#include "lib/odbc/connection.h"
#include "lib/odbc/detail/odbc_util.h"

namespace cebreiro::odbc
{
	constexpr SQLSMALLINT ENV_HANDLE_TYPE = SQL_HANDLE_ENV;

	DataSource::DataSource(DataSource&& rhs) noexcept
	{
		(void)operator=(std::move(rhs));
	}

	DataSource& DataSource::operator=(DataSource&& rhs) noexcept
	{
		DataSource::~DataSource();

		_dsn = std::move(rhs._dsn);
		_user = std::move(rhs._user);
		_password = std::move(rhs._password);
		_handle = rhs._handle;

		rhs._handle = nullptr;

		return *this;
	}

	DataSource::DataSource(std::string dsn, std::string user, std::string password)
		: _dsn(std::move(dsn))
		, _user(std::move(user))
		, _password(std::move(password))
	{
		SQLRETURN result = ::SQLAllocHandle(SQL_HANDLE_ENV,
			SQL_NULL_HANDLE,
			&_handle);
		detail::ThrowIfFail(result, ENV_HANDLE_TYPE, _handle);

		result = ::SQLSetEnvAttr(
			_handle,
			SQL_ATTR_ODBC_VERSION,
			reinterpret_cast<SQLPOINTER>(SQL_OV_ODBC3_80),
			SQL_IS_INTEGER);
		detail::ThrowIfFail(result, ENV_HANDLE_TYPE, _handle);
	}

	DataSource::~DataSource()
	{
		if (_handle)
		{
			[[maybe_unused]] SQLRETURN result = ::SQLFreeHandle(ENV_HANDLE_TYPE, _handle);
			assert(detail::IsSuccess(result));
		}
	}

	auto DataSource::MakeConnection() -> std::shared_ptr<Connection>
	{
		return std::make_shared<Connection>(*this, _dsn, _user, _password);
	}
}

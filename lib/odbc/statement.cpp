#include "statement.h"

#include <cassert>

#include "lib/odbc/connection.h"
#include "lib/odbc/detail/odbc_util.h"

namespace cebreiro::odbc
{
	constexpr SQLSMALLINT STMT_HANDLE_TYPE = SQL_HANDLE_STMT;

	Statement::Statement(Statement&& rhs) noexcept
	{
		(void)operator=(std::move(rhs));
	}

	Statement& Statement::operator=(Statement&& rhs) noexcept
	{
		Statement::~Statement();

		_handle = rhs._handle;

		rhs._handle = nullptr;

		return *this;
	}

	Statement::Statement(const Connection& connection)
	{
		SQLRETURN result = ::SQLAllocHandle(STMT_HANDLE_TYPE, connection._handle, &_handle);
		detail::ThrowIfFail(result, STMT_HANDLE_TYPE, _handle);
	}

	Statement::~Statement()
	{
		if (_handle)
		{
			[[maybe_unused]] SQLRETURN result = ::SQLFreeHandle(STMT_HANDLE_TYPE, _handle);
			assert(detail::IsSuccess(result));
		}
	}

	void Statement::Prepare(std::string query)
	{
		SQLRETURN result = ::SQLPrepareA(
			_handle,
			reinterpret_cast<SQLCHAR*>(query.data()),
			static_cast<SQLINTEGER>(query.length())
		);
		detail::ThrowIfFail(result, STMT_HANDLE_TYPE, _handle);
	}

	void Statement::Execute()
	{
		SQLRETURN result = ::SQLExecute(_handle);
		detail::ThrowIfFail(result, STMT_HANDLE_TYPE, _handle);
	}

	auto Statement::GetResultSet() -> ResultSet
	{
		return ResultSet(*this);
	}

	void Statement::SetNull(int32_t index)
	{
		SQLRETURN result = ::SQLBindParameter(
			_handle,
			static_cast<SQLUSMALLINT>(index),
			SQL_PARAM_INPUT,
			SQL_C_CHAR,
			SQL_CHAR,
			1,
			0,
			0,
			0,
			reinterpret_cast<SQLLEN*>(SQL_NULL_DATA)
		);
		detail::ThrowIfFail(result, STMT_HANDLE_TYPE, _handle);
	}

	void Statement::SetInt8(int32_t index, const int8_t& value)
	{
		SQLRETURN result = ::SQLBindParameter(
			_handle,
			static_cast<SQLUSMALLINT>(index),
			SQL_PARAM_INPUT,
			SQL_C_STINYINT,
			SQL_TINYINT,
			0,
			0,
			(int8_t*)&value,
			sizeof(int8_t),
			NULL
		);
		detail::ThrowIfFail(result, STMT_HANDLE_TYPE, _handle);
	}

	void Statement::SetUInt8(int32_t index, const uint8_t& value)
	{
		SQLRETURN result = ::SQLBindParameter(
			_handle,
			static_cast<SQLUSMALLINT>(index),
			SQL_PARAM_INPUT,
			SQL_C_UTINYINT,
			SQL_TINYINT,
			0,
			0,
			(uint8_t*)&value,
			sizeof(uint8_t),
			NULL
		);
		detail::ThrowIfFail(result, STMT_HANDLE_TYPE, _handle);
	}

	void Statement::SetInt16(int32_t index, const int16_t& value)
	{
		SQLRETURN result = ::SQLBindParameter(
			_handle,
			static_cast<SQLUSMALLINT>(index),
			SQL_PARAM_INPUT,
			SQL_C_SSHORT,
			SQL_SMALLINT,
			0,
			0,
			(int16_t*)&value,
			sizeof(int16_t),
			NULL
		);
		detail::ThrowIfFail(result, STMT_HANDLE_TYPE, _handle);
	}

	void Statement::SetUInt16(int32_t index, const uint16_t& value)
	{
		SQLRETURN result = ::SQLBindParameter(
			_handle,
			static_cast<SQLUSMALLINT>(index),
			SQL_PARAM_INPUT,
			SQL_C_USHORT,
			SQL_SMALLINT,
			0,
			0,
			(uint16_t*)&value,
			sizeof(uint16_t),
			NULL
		);
		detail::ThrowIfFail(result, STMT_HANDLE_TYPE, _handle);
	}

	void Statement::SetInt32(int32_t index, const int32_t& value)
	{
		SQLRETURN result = ::SQLBindParameter(
			_handle,
			static_cast<SQLUSMALLINT>(index),
			SQL_PARAM_INPUT,
			SQL_C_SLONG,
			SQL_INTEGER,
			0,
			0,
			(int32_t*)&value,
			sizeof(int32_t),
			NULL
		);
		detail::ThrowIfFail(result, STMT_HANDLE_TYPE, _handle);
	}

	void Statement::SetUInt32(int32_t index, const uint32_t& value)
	{
		SQLRETURN result = ::SQLBindParameter(
			_handle,
			static_cast<SQLUSMALLINT>(index),
			SQL_PARAM_INPUT,
			SQL_C_ULONG,
			SQL_INTEGER,
			0,
			0,
			(uint32_t*)&value,
			sizeof(uint32_t),
			NULL
		);
		detail::ThrowIfFail(result, STMT_HANDLE_TYPE, _handle);
	}

	void Statement::SetInt64(int32_t index, const int64_t& value)
	{
		SQLRETURN result = ::SQLBindParameter(
			_handle,
			static_cast<SQLUSMALLINT>(index),
			SQL_PARAM_INPUT,
			SQL_C_SBIGINT,
			SQL_BIGINT,
			0,
			0,
			(int64_t*)&value,
			sizeof(int64_t),
			NULL
		);
		detail::ThrowIfFail(result, STMT_HANDLE_TYPE, _handle);
	}

	void Statement::SetFloat32(int32_t index, const float& value)
	{
		SQLRETURN result = ::SQLBindParameter(
			_handle,
			static_cast<SQLUSMALLINT>(index),
			SQL_PARAM_INPUT,
			SQL_C_FLOAT,
			SQL_FLOAT,
			0,
			0,
			(float*)&value,
			sizeof(float),
			NULL
		);
		detail::ThrowIfFail(result, STMT_HANDLE_TYPE, _handle);
	}

	void Statement::SetFloat64(int32_t index, const double& value)
	{
		SQLRETURN result = ::SQLBindParameter(
			_handle,
			static_cast<SQLUSMALLINT>(index),
			SQL_PARAM_INPUT,
			SQL_C_DOUBLE,
			SQL_DOUBLE,
			0,
			0,
			(double*)&value,
			sizeof(double),
			NULL
		);
		detail::ThrowIfFail(result, STMT_HANDLE_TYPE, _handle);
	}

	void Statement::SetString(int32_t index, const std::string& value)
	{
		SQLRETURN result = ::SQLBindParameter(
			_handle,
			static_cast<SQLUSMALLINT>(index),
			SQL_PARAM_INPUT,
			SQL_C_CHAR,
			SQL_VARCHAR,
			0,
			0,
			(char*)value.c_str(),
			value.length(),
			NULL
		);
		detail::ThrowIfFail(result, STMT_HANDLE_TYPE, _handle);
	}
}

#include "result_set.h"

#include "lib/odbc/statement.h"
#include "lib/odbc/detail/odbc_util.h"

namespace cebreiro::odbc
{
	constexpr SQLSMALLINT STMT_HANDLE_TYPE = SQL_HANDLE_STMT;

	ResultSet::ResultSet(const Statement& statement)
		: _handle(statement._handle)
	{
	}

	ResultSet::~ResultSet()
	{
	}

	bool ResultSet::Fetch()
	{
		SQLRETURN result = ::SQLFetch(_handle);
		if (result == SQL_NO_DATA)
		{
			return false;
		}

		detail::ThrowIfFail(result, STMT_HANDLE_TYPE, _handle);

		return true;
	}

	bool ResultSet::Next()
	{
		SQLRETURN result = ::SQLMoreResults(_handle);
		if (result == SQL_NO_DATA)
		{
			return false;
		}

		detail::ThrowIfFail(result, STMT_HANDLE_TYPE, _handle);

		return true;
	}

	bool ResultSet::IsNull(int32_t index)
	{
		SQLLEN length = 0;
		char value = 0;

		SQLRETURN result = ::SQLGetData(
			_handle, 
			static_cast<SQLUSMALLINT>(index), 
			SQL_C_CHAR, 
			&value, 
			0, 
			&length);
		detail::ThrowIfFail(result, STMT_HANDLE_TYPE, _handle);

		return length == SQL_NULL_DATA;
	}

	auto ResultSet::GetInt8(int32_t index) -> int8_t
	{
		int8_t value = 0;

		SQLRETURN result = ::SQLGetData(
			_handle, 
			static_cast<SQLUSMALLINT>(index), 
			SQL_C_STINYINT, 
			&value, 
			0, 
			NULL);
		detail::ThrowIfFail(result, STMT_HANDLE_TYPE, _handle);

		return value;
	}

	auto ResultSet::GetUInt8(int32_t index) -> uint8_t
	{
		uint8_t value = 0;

		SQLRETURN result = ::SQLGetData(
			_handle, 
			static_cast<SQLUSMALLINT>(index), 
			SQL_C_UTINYINT, 
			&value, 
			0, 
			NULL);
		detail::ThrowIfFail(result, STMT_HANDLE_TYPE, _handle);

		return value;
	}

	auto ResultSet::GetInt16(int32_t index) -> int16_t
	{
		int16_t value = 0;

		SQLRETURN result = ::SQLGetData(
			_handle, 
			static_cast<SQLUSMALLINT>(index), 
			SQL_C_SSHORT, 
			&value, 
			0, 
			NULL);
		detail::ThrowIfFail(result, STMT_HANDLE_TYPE, _handle);

		return value;
	}

	auto ResultSet::GetUInt16(int32_t index) -> uint16_t
	{
		uint16_t value = 0;

		SQLRETURN result = ::SQLGetData(
			_handle, 
			static_cast<SQLUSMALLINT>(index), 
			SQL_C_USHORT, 
			&value, 
			0, 
			NULL);
		detail::ThrowIfFail(result, STMT_HANDLE_TYPE, _handle);

		return value;
	}

	auto ResultSet::GetInt32(int32_t index) -> int32_t
	{
		int32_t value = 0;

		SQLRETURN result = ::SQLGetData(
			_handle, 
			static_cast<SQLUSMALLINT>(index), 
			SQL_C_SLONG, 
			&value, 
			0, 
			NULL);
		detail::ThrowIfFail(result, STMT_HANDLE_TYPE, _handle);

		return value;
	}

	auto ResultSet::GetUInt32(int32_t index) -> uint32_t
	{
		uint32_t value = 0;

		SQLRETURN result = ::SQLGetData(
			_handle, 
			static_cast<SQLUSMALLINT>(index), 
			SQL_C_ULONG, 
			&value, 
			0, 
			NULL);
		detail::ThrowIfFail(result, STMT_HANDLE_TYPE, _handle);

		return value;
	}

	auto ResultSet::GetInt64(int32_t index) -> int64_t
	{
		int64_t value = 0;

		SQLRETURN result = ::SQLGetData(
			_handle, 
			static_cast<SQLUSMALLINT>(index), 
			SQL_C_SBIGINT, 
			&value, 
			0, 
			NULL);
		detail::ThrowIfFail(result, STMT_HANDLE_TYPE, _handle);

		return value;
	}

	auto ResultSet::GetFloat32(int32_t index) -> float
	{
		float value = 0;

		SQLRETURN result = ::SQLGetData(
			_handle, 
			static_cast<SQLUSMALLINT>(index), 
			SQL_C_FLOAT, 
			&value, 
			0, 
			NULL);
		detail::ThrowIfFail(result, STMT_HANDLE_TYPE, _handle);

		return value;
	}

	auto ResultSet::GetFloat64(int32_t index) -> double
	{
		double value = 0;

		SQLRETURN result = ::SQLGetData(
			_handle, 
			static_cast<SQLUSMALLINT>(index), 
			SQL_C_DOUBLE, 
			&value, 
			0, 
			NULL);
		detail::ThrowIfFail(result, STMT_HANDLE_TYPE, _handle);

		return value;
	}

	auto ResultSet::GetString(int32_t index) -> std::string
	{
		constexpr SQLLEN maxSize = 16384;
		char buffer[maxSize] = { 0, };

		SQLRETURN result = ::SQLGetData(
			_handle, 
			static_cast<SQLUSMALLINT>(index), 
			SQL_C_CHAR, 
			buffer, 
			maxSize, 
			NULL);
		detail::ThrowIfFail(result, STMT_HANDLE_TYPE, _handle);

		return buffer;
	}
}

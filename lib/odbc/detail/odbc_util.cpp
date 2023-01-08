#include "odbc_util.h"

#include <array>
#include <sstream>

#include "lib/common/string_util.h"
#include "lib/common/stacktrace_exception.h"

namespace cebreiro::odbc::detail
{
	bool IsSuccess(SQLRETURN result)
	{
		return (result == SQL_SUCCESS) || (result == SQL_SUCCESS_WITH_INFO);
	}

	bool CanUseAsyncNotification(SQLHANDLE connectionHandle)
	{
		SQLUINTEGER infoValue = 0;
		SQLLEN infoLength = 0;

		SQLRETURN result = SQLGetInfo(connectionHandle,
			SQL_ASYNC_NOTIFICATION,
			&infoValue,
			sizeof(infoValue),
			reinterpret_cast<SQLSMALLINT*>(&infoLength));

		ThrowIfFail(result, SQL_HANDLE_DBC, connectionHandle);

		return infoValue == SQL_ASYNC_NOTIFICATION_CAPABLE;
	}

	auto GetErrorMessage(SQLSMALLINT handleType, SQLHANDLE handle) -> std::string
	{
		SQLINTEGER nativeError = 0;
		SQLSMALLINT msgLength = 0;
		std::array<char, 1024> msg{ 0, };
		std::array<char, 32> sqlState{ 0, };
		std::wostringstream woss;

		SQLLEN recs = 0;
		::SQLGetDiagFieldA(
			handleType,
			handle,
			0,
			SQL_DIAG_NUMBER,
			&recs,
			0,
			0
		);

		bool success = false;
		for (SQLSMALLINT i = 0; i <= recs; ++i)
		{
			msg.fill(0);
			sqlState.fill(0);

			SQLRETURN result = ::SQLGetDiagRecA(
				handleType,
				handle,
				i,
				(SQLCHAR*)sqlState.data(),
				&nativeError,
				(SQLCHAR*)msg.data(),
				(SQLSMALLINT)msg.max_size(),
				&msgLength);

			if (IsSuccess(result))
			{
				woss << L"[SQLSTATE:" << sqlState.data() << L", " << msg.data() << L"]";
				success = true;
			}
		}

		if (success)
		{
			woss << L"\n";
		}

		return ToMBString(woss.str());
	}

	void ThrowIfFail(SQLRETURN result, SQLSMALLINT handleType, SQLHANDLE handle)
	{
		if (!IsSuccess(result))
		{
			throw StacktraceException(GetErrorMessage(handleType, handle));
		}
	}
}

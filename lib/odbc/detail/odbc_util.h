#pragma once
#include <string>
#include "lib/odbc/odbc_include.h"

namespace cebreiro::odbc::detail
{
	bool IsSuccess(SQLRETURN result);
	bool CanUseAsyncNotification(SQLHANDLE connectionHandle);

	auto GetErrorMessage(SQLSMALLINT handleType, SQLHANDLE handle) -> std::string;

	void ThrowIfFail(SQLRETURN result, SQLSMALLINT handleType, SQLHANDLE handle);
}
#pragma once
#include <cstdint>
#include <string>
#include <optional>
#include "db_option.h"

namespace cebreiro::gamebase
{
	struct Account
	{
		DB_OPTION(PK)
		int64_t id = -1;

		DB_OPTION(UNIQUE, MAX_LENGTH=30)
		std::string account;
		DB_OPTION(MAX_LENGTH=30)
		std::string password;

		int8_t gm_level = 0;

		std::optional<int8_t> banned = 0;

		DB_OPTION(MAX_LENGTH=1024)
		std::optional<std::string> ban_reason;
	};
}
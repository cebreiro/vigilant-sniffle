#pragma once
#include <string>
#include <memory>
#include "lib/odbc/odbc_include.h"

namespace cebreiro::odbc
{
	class Connection;

	class DataSource
	{
		friend class Connection;

	public:
		DataSource(DataSource&& rhs) noexcept;
		DataSource& operator=(DataSource&& rhs) noexcept;

		DataSource(std::string dsn, std::string user, std::string password);
		~DataSource();

		auto MakeConnection() -> std::shared_ptr<Connection>;

	private:
		SQLHENV _handle = nullptr;
		std::string _dsn;
		std::string _user;
		std::string _password;
	};
}

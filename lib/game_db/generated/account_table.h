#pragma once
#include <cstdint>
#include <memory>
#include <vector>

#include "lib/game_base/db/account.h"

namespace cebreiro::odbc { class Connection; }

namespace cebreiro::gamedb
{
	class AccountTable
	{
	public:
		AccountTable(odbc::Connection& connection);

		void CreateTable();
		void DropTable();

		void Add(const cebreiro::gamebase::Account& item);
		void Assign(const cebreiro::gamebase::Account& item);

		void RemoveByID(const int64_t& id);

		auto FindByID(const int64_t& id) -> std::optional<cebreiro::gamebase::Account>;
		auto FindByACCOUNT(const std::string& account) -> std::optional<cebreiro::gamebase::Account>;

		auto GetAll() -> std::vector<cebreiro::gamebase::Account>;

	private:
		odbc::Connection& _connection;
	};

}

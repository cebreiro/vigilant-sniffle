#include "account_table.h"

#include <cstdint>
#include <cassert>
#include <format>

#include "deserializer.h"
#include "lib/odbc/connection.h"

namespace cebreiro::gamedb
{
	AccountTable::AccountTable(odbc::Connection& connection)
		: _connection(connection)
	{
	}
	void AccountTable::CreateTable()
	{
		auto statement = _connection.GetStatement();
		statement.Prepare(R"delimiter(
		CREATE TABLE IF NOT EXISTS `Account` (
			`id` BIGINT NOT NULL
			, `account` VARCHAR(30) NOT NULL
			, `password` VARCHAR(30) NOT NULL
			, `gm_level` TINYINT NOT NULL
			, `banned` TINYINT
			, `ban_reason` VARCHAR(1024)
			, PRIMARY KEY(`id`)
			, UNIQUE KEY `Account_unique_account` (`account`)
		) ENGINE=InnoDB AUTO_INCREMENT=1 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
		)delimiter");
		statement.Execute();
	}
	void AccountTable::DropTable()
	{
		auto statement = _connection.GetStatement();
		statement.Prepare(R"delimiter(
		DROP TABLE IF EXISTS `Account`;
		)delimiter");
		statement.Execute();
	}
	void AccountTable::Add(const cebreiro::gamebase::Account& item)
	{
		auto statement = _connection.GetStatement();
		statement.Prepare(R"delimiter(
			INSERT INTO `Account`
				(`id`, `account`, `password`, `gm_level`, `banned`, `ban_reason`)
			VALUES
				(?, ?, ?, ?, ?, ?);
		)delimiter");
		statement.Set<int64_t>(1, item.id);
		statement.Set<std::string>(2, item.account);
		statement.Set<std::string>(3, item.password);
		statement.Set<int8_t>(4, item.gm_level);
		statement.Set<std::optional<int8_t>>(5, item.banned);
		statement.Set<std::optional<std::string>>(6, item.ban_reason);
		statement.Execute();
	}
	void AccountTable::Assign(const cebreiro::gamebase::Account& item)
	{
		auto statement = _connection.GetStatement();
		statement.Prepare(R"delimiter(
			INSERT INTO `Account`
				(`id`, `account`, `password`, `gm_level`, `banned`, `ban_reason`)
			VALUES
				(?, ?, ?, ?, ?, ?)
			ON DUPLICATE KEY UPDATE
				(`account` = ?, `password` = ?, `gm_level` = ?, `banned` = ?, `ban_reason` = ?);
		)delimiter");
		statement.Set<int64_t>(1, item.id);
		statement.Set<std::string>(2, item.account);
		statement.Set<std::string>(3, item.password);
		statement.Set<int8_t>(4, item.gm_level);
		statement.Set<std::optional<int8_t>>(5, item.banned);
		statement.Set<std::optional<std::string>>(6, item.ban_reason);
		statement.Set<std::string>(7, item.account);
		statement.Set<std::string>(8, item.password);
		statement.Set<int8_t>(9, item.gm_level);
		statement.Set<std::optional<int8_t>>(10, item.banned);
		statement.Set<std::optional<std::string>>(11, item.ban_reason);
		statement.Execute();
	}
	void AccountTable::RemoveByID(const int64_t& id)
	{
		auto statement = _connection.GetStatement();
		statement.Prepare(R"delimiter(
			DELETE FROM `Account`
				WHERE `id` = ?;
			
		)delimiter");
		
		statement.Set<int64_t>(1, id);
		statement.Execute();
	}
	auto AccountTable::FindByID(const int64_t& id) -> std::optional<cebreiro::gamebase::Account>
	{
		auto statement = _connection.GetStatement();
		statement.Prepare(R"delimiter(
			SELECT * FROM `Account`
				WHERE `id` = ?;
			
		)delimiter");
		
		statement.Set<int64_t>(1, id);
		statement.Execute();

		auto resultSet = statement.GetResultSet();
		if (resultSet.Fetch())
		{
			return Deserializer<cebreiro::gamebase::Account>::Deserialize(resultSet);
		}
		return std::nullopt;
	}
	auto AccountTable::FindByACCOUNT(const std::string& account) -> std::optional<cebreiro::gamebase::Account>
	{
		auto statement = _connection.GetStatement();
		statement.Prepare(R"delimiter(
			SELECT * FROM `Account`
				WHERE `account` = ?;
			
		)delimiter");
		
		statement.Set<std::string>(1, account);
		statement.Execute();

		auto resultSet = statement.GetResultSet();
		if (resultSet.Fetch())
		{
			return Deserializer<cebreiro::gamebase::Account>::Deserialize(resultSet);
		}
		return std::nullopt;
	}
	auto AccountTable::GetAll() -> std::vector<cebreiro::gamebase::Account>
	{
		auto statement = _connection.GetStatement();
		statement.Prepare(R"delimiter(
			SELECT * FROM `Account`
			
		)delimiter");
		
		statement.Execute();

		std::vector<cebreiro::gamebase::Account> result;
		auto resultSet = statement.GetResultSet();
		while (resultSet.Fetch())
		{
			result.push_back(Deserializer<cebreiro::gamebase::Account>::Deserialize(resultSet));
		}
		return result;
	}
}

#include "character_table.h"

#include <cstdint>
#include <cassert>
#include <format>

#include "deserializer.h"
#include "lib/odbc/connection.h"

namespace cebreiro::gamedb
{
	CharacterTable::CharacterTable(odbc::Connection& connection)
		: _connection(connection)
	{
	}
	void CharacterTable::CreateTable()
	{
		auto statement = _connection.GetStatement();
		statement.Prepare(R"delimiter(
		CREATE TABLE IF NOT EXISTS `Character` (
			`id` BIGINT NOT NULL
			, `aid` BIGINT NOT NULL
			, `wid` TINYINT NOT NULL
			, `slot` TINYINT NOT NULL
			, `name` VARCHAR(30) NOT NULL
			, `hair_color` INT NOT NULL
			, `hair` INT NOT NULL
			, `skin_color` INT NOT NULL
			, `face` INT NOT NULL
			, `arms` TINYINT NOT NULL
			, `running` TINYINT NOT NULL
			, `gold` INT NOT NULL
			, `inventory_page` TINYINT NOT NULL
			, `zone` INT NOT NULL
			, `stage` INT NOT NULL
			, `x` FLOAT NOT NULL
			, `y` FLOAT NOT NULL
			, PRIMARY KEY(`id`)
			, CONSTRAINT `Character_fk_aid` FOREIGN KEY (`aid`)
				REFERENCES `Account` (`id`)
				ON DELETE CASCADE ON UPDATE CASCADE
			, UNIQUE KEY `Character_unique_name` (`name`)
		) ENGINE=InnoDB AUTO_INCREMENT=1 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
		)delimiter");
		statement.Execute();
	}
	void CharacterTable::DropTable()
	{
		auto statement = _connection.GetStatement();
		statement.Prepare(R"delimiter(
		DROP TABLE IF EXISTS `Character`;
		)delimiter");
		statement.Execute();
	}
	void CharacterTable::Add(const cebreiro::gamebase::Character& item)
	{
		auto statement = _connection.GetStatement();
		statement.Prepare(R"delimiter(
			INSERT INTO `Character`
				(`id`, `aid`, `wid`, `slot`, `name`, `hair_color`, `hair`, `skin_color`, `face`, `arms`, `running`, `gold`, `inventory_page`, `zone`, `stage`, `x`, `y`)
			VALUES
				(?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?);
		)delimiter");
		statement.Set<int64_t>(1, item.id);
		statement.Set<int64_t>(2, item.aid);
		statement.Set<int8_t>(3, item.wid);
		statement.Set<int8_t>(4, item.slot);
		statement.Set<std::string>(5, item.name);
		statement.Set<int32_t>(6, item.hair_color);
		statement.Set<int32_t>(7, item.hair);
		statement.Set<int32_t>(8, item.skin_color);
		statement.Set<int32_t>(9, item.face);
		statement.Set<int8_t>(10, item.arms);
		statement.Set<int8_t>(11, item.running);
		statement.Set<int32_t>(12, item.gold);
		statement.Set<int8_t>(13, item.inventory_page);
		statement.Set<int32_t>(14, item.zone);
		statement.Set<int32_t>(15, item.stage);
		statement.Set<float>(16, item.x);
		statement.Set<float>(17, item.y);
		statement.Execute();
	}
	void CharacterTable::Assign(const cebreiro::gamebase::Character& item)
	{
		auto statement = _connection.GetStatement();
		statement.Prepare(R"delimiter(
			INSERT INTO `Character`
				(`id`, `aid`, `wid`, `slot`, `name`, `hair_color`, `hair`, `skin_color`, `face`, `arms`, `running`, `gold`, `inventory_page`, `zone`, `stage`, `x`, `y`)
			VALUES
				(?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)
			ON DUPLICATE KEY UPDATE
				(`wid` = ?, `slot` = ?, `name` = ?, `hair_color` = ?, `hair` = ?, `skin_color` = ?, `face` = ?, `arms` = ?, `running` = ?, `gold` = ?, `inventory_page` = ?, `zone` = ?, `stage` = ?, `x` = ?, `y` = ?);
		)delimiter");
		statement.Set<int64_t>(1, item.id);
		statement.Set<int64_t>(2, item.aid);
		statement.Set<int8_t>(3, item.wid);
		statement.Set<int8_t>(4, item.slot);
		statement.Set<std::string>(5, item.name);
		statement.Set<int32_t>(6, item.hair_color);
		statement.Set<int32_t>(7, item.hair);
		statement.Set<int32_t>(8, item.skin_color);
		statement.Set<int32_t>(9, item.face);
		statement.Set<int8_t>(10, item.arms);
		statement.Set<int8_t>(11, item.running);
		statement.Set<int32_t>(12, item.gold);
		statement.Set<int8_t>(13, item.inventory_page);
		statement.Set<int32_t>(14, item.zone);
		statement.Set<int32_t>(15, item.stage);
		statement.Set<float>(16, item.x);
		statement.Set<float>(17, item.y);
		statement.Set<int8_t>(18, item.wid);
		statement.Set<int8_t>(19, item.slot);
		statement.Set<std::string>(20, item.name);
		statement.Set<int32_t>(21, item.hair_color);
		statement.Set<int32_t>(22, item.hair);
		statement.Set<int32_t>(23, item.skin_color);
		statement.Set<int32_t>(24, item.face);
		statement.Set<int8_t>(25, item.arms);
		statement.Set<int8_t>(26, item.running);
		statement.Set<int32_t>(27, item.gold);
		statement.Set<int8_t>(28, item.inventory_page);
		statement.Set<int32_t>(29, item.zone);
		statement.Set<int32_t>(30, item.stage);
		statement.Set<float>(31, item.x);
		statement.Set<float>(32, item.y);
		statement.Execute();
	}
	void CharacterTable::RemoveByID(const int64_t& id)
	{
		auto statement = _connection.GetStatement();
		statement.Prepare(R"delimiter(
			DELETE FROM `Character`
				WHERE `id` = ?;
			
		)delimiter");
		
		statement.Set<int64_t>(1, id);
		statement.Execute();
	}
	void CharacterTable::RemoveByAID(const int64_t& aid)
	{
		auto statement = _connection.GetStatement();
		statement.Prepare(R"delimiter(
			DELETE FROM `Character`
				WHERE `aid` = ?;
			
		)delimiter");
		
		statement.Set<int64_t>(1, aid);
		statement.Execute();
	}
	auto CharacterTable::FindByID(const int64_t& id) -> std::optional<cebreiro::gamebase::Character>
	{
		auto statement = _connection.GetStatement();
		statement.Prepare(R"delimiter(
			SELECT * FROM `Character`
				WHERE `id` = ?;
			
		)delimiter");
		
		statement.Set<int64_t>(1, id);
		statement.Execute();

		auto resultSet = statement.GetResultSet();
		if (resultSet.Fetch())
		{
			return Deserializer<cebreiro::gamebase::Character>::Deserialize(resultSet);
		}
		return std::nullopt;
	}
	auto CharacterTable::FindByNAME(const std::string& name) -> std::optional<cebreiro::gamebase::Character>
	{
		auto statement = _connection.GetStatement();
		statement.Prepare(R"delimiter(
			SELECT * FROM `Character`
				WHERE `name` = ?;
			
		)delimiter");
		
		statement.Set<std::string>(1, name);
		statement.Execute();

		auto resultSet = statement.GetResultSet();
		if (resultSet.Fetch())
		{
			return Deserializer<cebreiro::gamebase::Character>::Deserialize(resultSet);
		}
		return std::nullopt;
	}
	auto CharacterTable::FindByAID(const int64_t& aid) -> std::vector<cebreiro::gamebase::Character>
	{
		auto statement = _connection.GetStatement();
		statement.Prepare(R"delimiter(
			SELECT * FROM `Character`
				WHERE `aid` = ?;
			
		)delimiter");
		
		statement.Set<int64_t>(1, aid);
		statement.Execute();

		std::vector<cebreiro::gamebase::Character> result;
		auto resultSet = statement.GetResultSet();
		while (resultSet.Fetch())
		{
			result.push_back(Deserializer<cebreiro::gamebase::Character>::Deserialize(resultSet));
		}
		return result;
	}
	auto CharacterTable::GetAll() -> std::vector<cebreiro::gamebase::Character>
	{
		auto statement = _connection.GetStatement();
		statement.Prepare(R"delimiter(
			SELECT * FROM `Character`
			
		)delimiter");
		
		statement.Execute();

		std::vector<cebreiro::gamebase::Character> result;
		auto resultSet = statement.GetResultSet();
		while (resultSet.Fetch())
		{
			result.push_back(Deserializer<cebreiro::gamebase::Character>::Deserialize(resultSet));
		}
		return result;
	}
	CharacterStatTable::CharacterStatTable(odbc::Connection& connection)
		: _connection(connection)
	{
	}
	void CharacterStatTable::CreateTable()
	{
		auto statement = _connection.GetStatement();
		statement.Prepare(R"delimiter(
		CREATE TABLE IF NOT EXISTS `CharacterStat` (
			`cid` BIGINT NOT NULL
			, `gender` TINYINT NOT NULL
			, `hp` INT NOT NULL
			, `mp` INT NOT NULL
			, `chr_lv` INT NOT NULL
			, `chr_exp` INT NOT NULL
			, `str` INT NOT NULL
			, `dex` INT NOT NULL
			, `accr` INT NOT NULL
			, `health` INT NOT NULL
			, `intell` INT NOT NULL
			, `wis` INT NOT NULL
			, `will` INT NOT NULL
			, `stat_point` INT NOT NULL
			, `water` TINYINT NOT NULL
			, `fire` TINYINT NOT NULL
			, `lightning` TINYINT NOT NULL
			, UNIQUE KEY `CharacterStat_unique_cid` (`cid`)
			, CONSTRAINT `CharacterStat_fk_cid` FOREIGN KEY (`cid`)
				REFERENCES `Character` (`id`)
				ON DELETE CASCADE ON UPDATE CASCADE
		) ENGINE=InnoDB AUTO_INCREMENT=1 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
		)delimiter");
		statement.Execute();
	}
	void CharacterStatTable::DropTable()
	{
		auto statement = _connection.GetStatement();
		statement.Prepare(R"delimiter(
		DROP TABLE IF EXISTS `CharacterStat`;
		)delimiter");
		statement.Execute();
	}
	void CharacterStatTable::Add(const cebreiro::gamebase::CharacterStat& item)
	{
		auto statement = _connection.GetStatement();
		statement.Prepare(R"delimiter(
			INSERT INTO `CharacterStat`
				(`cid`, `gender`, `hp`, `mp`, `chr_lv`, `chr_exp`, `str`, `dex`, `accr`, `health`, `intell`, `wis`, `will`, `stat_point`, `water`, `fire`, `lightning`)
			VALUES
				(?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?);
		)delimiter");
		statement.Set<int64_t>(1, item.cid);
		statement.Set<int8_t>(2, item.gender);
		statement.Set<int32_t>(3, item.hp);
		statement.Set<int32_t>(4, item.mp);
		statement.Set<int32_t>(5, item.chr_lv);
		statement.Set<int32_t>(6, item.chr_exp);
		statement.Set<int32_t>(7, item.str);
		statement.Set<int32_t>(8, item.dex);
		statement.Set<int32_t>(9, item.accr);
		statement.Set<int32_t>(10, item.health);
		statement.Set<int32_t>(11, item.intell);
		statement.Set<int32_t>(12, item.wis);
		statement.Set<int32_t>(13, item.will);
		statement.Set<int32_t>(14, item.stat_point);
		statement.Set<int8_t>(15, item.water);
		statement.Set<int8_t>(16, item.fire);
		statement.Set<int8_t>(17, item.lightning);
		statement.Execute();
	}
	void CharacterStatTable::Assign(const cebreiro::gamebase::CharacterStat& item)
	{
		auto statement = _connection.GetStatement();
		statement.Prepare(R"delimiter(
			INSERT INTO `CharacterStat`
				(`cid`, `gender`, `hp`, `mp`, `chr_lv`, `chr_exp`, `str`, `dex`, `accr`, `health`, `intell`, `wis`, `will`, `stat_point`, `water`, `fire`, `lightning`)
			VALUES
				(?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)
			ON DUPLICATE KEY UPDATE
				(`gender` = ?, `hp` = ?, `mp` = ?, `chr_lv` = ?, `chr_exp` = ?, `str` = ?, `dex` = ?, `accr` = ?, `health` = ?, `intell` = ?, `wis` = ?, `will` = ?, `stat_point` = ?, `water` = ?, `fire` = ?, `lightning` = ?);
		)delimiter");
		statement.Set<int64_t>(1, item.cid);
		statement.Set<int8_t>(2, item.gender);
		statement.Set<int32_t>(3, item.hp);
		statement.Set<int32_t>(4, item.mp);
		statement.Set<int32_t>(5, item.chr_lv);
		statement.Set<int32_t>(6, item.chr_exp);
		statement.Set<int32_t>(7, item.str);
		statement.Set<int32_t>(8, item.dex);
		statement.Set<int32_t>(9, item.accr);
		statement.Set<int32_t>(10, item.health);
		statement.Set<int32_t>(11, item.intell);
		statement.Set<int32_t>(12, item.wis);
		statement.Set<int32_t>(13, item.will);
		statement.Set<int32_t>(14, item.stat_point);
		statement.Set<int8_t>(15, item.water);
		statement.Set<int8_t>(16, item.fire);
		statement.Set<int8_t>(17, item.lightning);
		statement.Set<int8_t>(18, item.gender);
		statement.Set<int32_t>(19, item.hp);
		statement.Set<int32_t>(20, item.mp);
		statement.Set<int32_t>(21, item.chr_lv);
		statement.Set<int32_t>(22, item.chr_exp);
		statement.Set<int32_t>(23, item.str);
		statement.Set<int32_t>(24, item.dex);
		statement.Set<int32_t>(25, item.accr);
		statement.Set<int32_t>(26, item.health);
		statement.Set<int32_t>(27, item.intell);
		statement.Set<int32_t>(28, item.wis);
		statement.Set<int32_t>(29, item.will);
		statement.Set<int32_t>(30, item.stat_point);
		statement.Set<int8_t>(31, item.water);
		statement.Set<int8_t>(32, item.fire);
		statement.Set<int8_t>(33, item.lightning);
		statement.Execute();
	}
	void CharacterStatTable::RemoveByCID(const int64_t& cid)
	{
		auto statement = _connection.GetStatement();
		statement.Prepare(R"delimiter(
			DELETE FROM `CharacterStat`
				WHERE `cid` = ?;
			
		)delimiter");
		
		statement.Set<int64_t>(1, cid);
		statement.Execute();
	}
	auto CharacterStatTable::FindByCID(const int64_t& cid) -> std::optional<cebreiro::gamebase::CharacterStat>
	{
		auto statement = _connection.GetStatement();
		statement.Prepare(R"delimiter(
			SELECT * FROM `CharacterStat`
				WHERE `cid` = ?;
			
		)delimiter");
		
		statement.Set<int64_t>(1, cid);
		statement.Execute();

		auto resultSet = statement.GetResultSet();
		if (resultSet.Fetch())
		{
			return Deserializer<cebreiro::gamebase::CharacterStat>::Deserialize(resultSet);
		}
		return std::nullopt;
	}
	auto CharacterStatTable::GetAll() -> std::vector<cebreiro::gamebase::CharacterStat>
	{
		auto statement = _connection.GetStatement();
		statement.Prepare(R"delimiter(
			SELECT * FROM `CharacterStat`
			
		)delimiter");
		
		statement.Execute();

		std::vector<cebreiro::gamebase::CharacterStat> result;
		auto resultSet = statement.GetResultSet();
		while (resultSet.Fetch())
		{
			result.push_back(Deserializer<cebreiro::gamebase::CharacterStat>::Deserialize(resultSet));
		}
		return result;
	}
	CharacterJobTable::CharacterJobTable(odbc::Connection& connection)
		: _connection(connection)
	{
	}
	void CharacterJobTable::CreateTable()
	{
		auto statement = _connection.GetStatement();
		statement.Prepare(R"delimiter(
		CREATE TABLE IF NOT EXISTS `CharacterJob` (
			`cid` BIGINT NOT NULL
			, `job1` INT NOT NULL
			, `job1_level` INT NOT NULL
			, `job1_exp` INT NOT NULL
			, `job1_sp` INT NOT NULL
			, `job2` INT NOT NULL
			, `job2_level` INT NOT NULL
			, `job2_exp` INT NOT NULL
			, `job2_sp` INT NOT NULL
			, `job3` INT NOT NULL
			, `job3_level` INT NOT NULL
			, `job3_exp` INT NOT NULL
			, `job3_sp` INT NOT NULL
			, `job_sub` INT NOT NULL
			, `job_sub_level` INT NOT NULL
			, `job_sub_exp` INT NOT NULL
			, `job_sub_sp` INT NOT NULL
			, UNIQUE KEY `CharacterJob_unique_cid` (`cid`)
			, CONSTRAINT `CharacterJob_fk_cid` FOREIGN KEY (`cid`)
				REFERENCES `Character` (`id`)
				ON DELETE CASCADE ON UPDATE CASCADE
		) ENGINE=InnoDB AUTO_INCREMENT=1 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
		)delimiter");
		statement.Execute();
	}
	void CharacterJobTable::DropTable()
	{
		auto statement = _connection.GetStatement();
		statement.Prepare(R"delimiter(
		DROP TABLE IF EXISTS `CharacterJob`;
		)delimiter");
		statement.Execute();
	}
	void CharacterJobTable::Add(const cebreiro::gamebase::CharacterJob& item)
	{
		auto statement = _connection.GetStatement();
		statement.Prepare(R"delimiter(
			INSERT INTO `CharacterJob`
				(`cid`, `job1`, `job1_level`, `job1_exp`, `job1_sp`, `job2`, `job2_level`, `job2_exp`, `job2_sp`, `job3`, `job3_level`, `job3_exp`, `job3_sp`, `job_sub`, `job_sub_level`, `job_sub_exp`, `job_sub_sp`)
			VALUES
				(?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?);
		)delimiter");
		statement.Set<int64_t>(1, item.cid);
		statement.Set<int32_t>(2, item.job1);
		statement.Set<int32_t>(3, item.job1_level);
		statement.Set<int32_t>(4, item.job1_exp);
		statement.Set<int32_t>(5, item.job1_sp);
		statement.Set<int32_t>(6, item.job2);
		statement.Set<int32_t>(7, item.job2_level);
		statement.Set<int32_t>(8, item.job2_exp);
		statement.Set<int32_t>(9, item.job2_sp);
		statement.Set<int32_t>(10, item.job3);
		statement.Set<int32_t>(11, item.job3_level);
		statement.Set<int32_t>(12, item.job3_exp);
		statement.Set<int32_t>(13, item.job3_sp);
		statement.Set<int32_t>(14, item.job_sub);
		statement.Set<int32_t>(15, item.job_sub_level);
		statement.Set<int32_t>(16, item.job_sub_exp);
		statement.Set<int32_t>(17, item.job_sub_sp);
		statement.Execute();
	}
	void CharacterJobTable::Assign(const cebreiro::gamebase::CharacterJob& item)
	{
		auto statement = _connection.GetStatement();
		statement.Prepare(R"delimiter(
			INSERT INTO `CharacterJob`
				(`cid`, `job1`, `job1_level`, `job1_exp`, `job1_sp`, `job2`, `job2_level`, `job2_exp`, `job2_sp`, `job3`, `job3_level`, `job3_exp`, `job3_sp`, `job_sub`, `job_sub_level`, `job_sub_exp`, `job_sub_sp`)
			VALUES
				(?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)
			ON DUPLICATE KEY UPDATE
				(`job1` = ?, `job1_level` = ?, `job1_exp` = ?, `job1_sp` = ?, `job2` = ?, `job2_level` = ?, `job2_exp` = ?, `job2_sp` = ?, `job3` = ?, `job3_level` = ?, `job3_exp` = ?, `job3_sp` = ?, `job_sub` = ?, `job_sub_level` = ?, `job_sub_exp` = ?, `job_sub_sp` = ?);
		)delimiter");
		statement.Set<int64_t>(1, item.cid);
		statement.Set<int32_t>(2, item.job1);
		statement.Set<int32_t>(3, item.job1_level);
		statement.Set<int32_t>(4, item.job1_exp);
		statement.Set<int32_t>(5, item.job1_sp);
		statement.Set<int32_t>(6, item.job2);
		statement.Set<int32_t>(7, item.job2_level);
		statement.Set<int32_t>(8, item.job2_exp);
		statement.Set<int32_t>(9, item.job2_sp);
		statement.Set<int32_t>(10, item.job3);
		statement.Set<int32_t>(11, item.job3_level);
		statement.Set<int32_t>(12, item.job3_exp);
		statement.Set<int32_t>(13, item.job3_sp);
		statement.Set<int32_t>(14, item.job_sub);
		statement.Set<int32_t>(15, item.job_sub_level);
		statement.Set<int32_t>(16, item.job_sub_exp);
		statement.Set<int32_t>(17, item.job_sub_sp);
		statement.Set<int32_t>(18, item.job1);
		statement.Set<int32_t>(19, item.job1_level);
		statement.Set<int32_t>(20, item.job1_exp);
		statement.Set<int32_t>(21, item.job1_sp);
		statement.Set<int32_t>(22, item.job2);
		statement.Set<int32_t>(23, item.job2_level);
		statement.Set<int32_t>(24, item.job2_exp);
		statement.Set<int32_t>(25, item.job2_sp);
		statement.Set<int32_t>(26, item.job3);
		statement.Set<int32_t>(27, item.job3_level);
		statement.Set<int32_t>(28, item.job3_exp);
		statement.Set<int32_t>(29, item.job3_sp);
		statement.Set<int32_t>(30, item.job_sub);
		statement.Set<int32_t>(31, item.job_sub_level);
		statement.Set<int32_t>(32, item.job_sub_exp);
		statement.Set<int32_t>(33, item.job_sub_sp);
		statement.Execute();
	}
	void CharacterJobTable::RemoveByCID(const int64_t& cid)
	{
		auto statement = _connection.GetStatement();
		statement.Prepare(R"delimiter(
			DELETE FROM `CharacterJob`
				WHERE `cid` = ?;
			
		)delimiter");
		
		statement.Set<int64_t>(1, cid);
		statement.Execute();
	}
	auto CharacterJobTable::FindByCID(const int64_t& cid) -> std::optional<cebreiro::gamebase::CharacterJob>
	{
		auto statement = _connection.GetStatement();
		statement.Prepare(R"delimiter(
			SELECT * FROM `CharacterJob`
				WHERE `cid` = ?;
			
		)delimiter");
		
		statement.Set<int64_t>(1, cid);
		statement.Execute();

		auto resultSet = statement.GetResultSet();
		if (resultSet.Fetch())
		{
			return Deserializer<cebreiro::gamebase::CharacterJob>::Deserialize(resultSet);
		}
		return std::nullopt;
	}
	auto CharacterJobTable::GetAll() -> std::vector<cebreiro::gamebase::CharacterJob>
	{
		auto statement = _connection.GetStatement();
		statement.Prepare(R"delimiter(
			SELECT * FROM `CharacterJob`
			
		)delimiter");
		
		statement.Execute();

		std::vector<cebreiro::gamebase::CharacterJob> result;
		auto resultSet = statement.GetResultSet();
		while (resultSet.Fetch())
		{
			result.push_back(Deserializer<cebreiro::gamebase::CharacterJob>::Deserialize(resultSet));
		}
		return result;
	}
	CharacterItemTable::CharacterItemTable(odbc::Connection& connection)
		: _connection(connection)
	{
	}
	void CharacterItemTable::CreateTable()
	{
		auto statement = _connection.GetStatement();
		statement.Prepare(R"delimiter(
		CREATE TABLE IF NOT EXISTS `CharacterItem` (
			`id` BIGINT NOT NULL
			, `cid` BIGINT NOT NULL
			, `item_id` INT NOT NULL
			, `quantity` INT NOT NULL
			, `equip_position` TINYINT NOT NULL
			, `page` TINYINT NOT NULL
			, `x` TINYINT NOT NULL
			, `y` TINYINT NOT NULL
			, `is_in_quick` TINYINT NOT NULL
			, `is_pick` TINYINT NOT NULL
			, PRIMARY KEY(`id`)
			, CONSTRAINT `CharacterItem_fk_cid` FOREIGN KEY (`cid`)
				REFERENCES `Character` (`id`)
				ON DELETE CASCADE ON UPDATE CASCADE
		) ENGINE=InnoDB AUTO_INCREMENT=1 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
		)delimiter");
		statement.Execute();
	}
	void CharacterItemTable::DropTable()
	{
		auto statement = _connection.GetStatement();
		statement.Prepare(R"delimiter(
		DROP TABLE IF EXISTS `CharacterItem`;
		)delimiter");
		statement.Execute();
	}
	void CharacterItemTable::Add(const cebreiro::gamebase::CharacterItem& item)
	{
		auto statement = _connection.GetStatement();
		statement.Prepare(R"delimiter(
			INSERT INTO `CharacterItem`
				(`id`, `cid`, `item_id`, `quantity`, `equip_position`, `page`, `x`, `y`, `is_in_quick`, `is_pick`)
			VALUES
				(?, ?, ?, ?, ?, ?, ?, ?, ?, ?);
		)delimiter");
		statement.Set<int64_t>(1, item.id);
		statement.Set<int64_t>(2, item.cid);
		statement.Set<int32_t>(3, item.item_id);
		statement.Set<int32_t>(4, item.quantity);
		statement.Set<int8_t>(5, item.equip_position);
		statement.Set<int8_t>(6, item.page);
		statement.Set<int8_t>(7, item.x);
		statement.Set<int8_t>(8, item.y);
		statement.Set<int8_t>(9, item.is_in_quick);
		statement.Set<int8_t>(10, item.is_pick);
		statement.Execute();
	}
	void CharacterItemTable::Assign(const cebreiro::gamebase::CharacterItem& item)
	{
		auto statement = _connection.GetStatement();
		statement.Prepare(R"delimiter(
			INSERT INTO `CharacterItem`
				(`id`, `cid`, `item_id`, `quantity`, `equip_position`, `page`, `x`, `y`, `is_in_quick`, `is_pick`)
			VALUES
				(?, ?, ?, ?, ?, ?, ?, ?, ?, ?)
			ON DUPLICATE KEY UPDATE
				(`item_id` = ?, `quantity` = ?, `equip_position` = ?, `page` = ?, `x` = ?, `y` = ?, `is_in_quick` = ?, `is_pick` = ?);
		)delimiter");
		statement.Set<int64_t>(1, item.id);
		statement.Set<int64_t>(2, item.cid);
		statement.Set<int32_t>(3, item.item_id);
		statement.Set<int32_t>(4, item.quantity);
		statement.Set<int8_t>(5, item.equip_position);
		statement.Set<int8_t>(6, item.page);
		statement.Set<int8_t>(7, item.x);
		statement.Set<int8_t>(8, item.y);
		statement.Set<int8_t>(9, item.is_in_quick);
		statement.Set<int8_t>(10, item.is_pick);
		statement.Set<int32_t>(11, item.item_id);
		statement.Set<int32_t>(12, item.quantity);
		statement.Set<int8_t>(13, item.equip_position);
		statement.Set<int8_t>(14, item.page);
		statement.Set<int8_t>(15, item.x);
		statement.Set<int8_t>(16, item.y);
		statement.Set<int8_t>(17, item.is_in_quick);
		statement.Set<int8_t>(18, item.is_pick);
		statement.Execute();
	}
	void CharacterItemTable::RemoveByID(const int64_t& id)
	{
		auto statement = _connection.GetStatement();
		statement.Prepare(R"delimiter(
			DELETE FROM `CharacterItem`
				WHERE `id` = ?;
			
		)delimiter");
		
		statement.Set<int64_t>(1, id);
		statement.Execute();
	}
	void CharacterItemTable::RemoveByCID(const int64_t& cid)
	{
		auto statement = _connection.GetStatement();
		statement.Prepare(R"delimiter(
			DELETE FROM `CharacterItem`
				WHERE `cid` = ?;
			
		)delimiter");
		
		statement.Set<int64_t>(1, cid);
		statement.Execute();
	}
	auto CharacterItemTable::FindByID(const int64_t& id) -> std::optional<cebreiro::gamebase::CharacterItem>
	{
		auto statement = _connection.GetStatement();
		statement.Prepare(R"delimiter(
			SELECT * FROM `CharacterItem`
				WHERE `id` = ?;
			
		)delimiter");
		
		statement.Set<int64_t>(1, id);
		statement.Execute();

		auto resultSet = statement.GetResultSet();
		if (resultSet.Fetch())
		{
			return Deserializer<cebreiro::gamebase::CharacterItem>::Deserialize(resultSet);
		}
		return std::nullopt;
	}
	auto CharacterItemTable::FindByCID(const int64_t& cid) -> std::vector<cebreiro::gamebase::CharacterItem>
	{
		auto statement = _connection.GetStatement();
		statement.Prepare(R"delimiter(
			SELECT * FROM `CharacterItem`
				WHERE `cid` = ?;
			
		)delimiter");
		
		statement.Set<int64_t>(1, cid);
		statement.Execute();

		std::vector<cebreiro::gamebase::CharacterItem> result;
		auto resultSet = statement.GetResultSet();
		while (resultSet.Fetch())
		{
			result.push_back(Deserializer<cebreiro::gamebase::CharacterItem>::Deserialize(resultSet));
		}
		return result;
	}
	auto CharacterItemTable::GetAll() -> std::vector<cebreiro::gamebase::CharacterItem>
	{
		auto statement = _connection.GetStatement();
		statement.Prepare(R"delimiter(
			SELECT * FROM `CharacterItem`
			
		)delimiter");
		
		statement.Execute();

		std::vector<cebreiro::gamebase::CharacterItem> result;
		auto resultSet = statement.GetResultSet();
		while (resultSet.Fetch())
		{
			result.push_back(Deserializer<cebreiro::gamebase::CharacterItem>::Deserialize(resultSet));
		}
		return result;
	}
	CharacterSkillTable::CharacterSkillTable(odbc::Connection& connection)
		: _connection(connection)
	{
	}
	void CharacterSkillTable::CreateTable()
	{
		auto statement = _connection.GetStatement();
		statement.Prepare(R"delimiter(
		CREATE TABLE IF NOT EXISTS `CharacterSkill` (
			`cid` BIGINT NOT NULL
			, `skill_id` INT NOT NULL
			, `job` INT NOT NULL
			, `level` INT NOT NULL
			, `cooldown` INT NOT NULL
			, `page` TINYINT NOT NULL
			, `x` TINYINT NOT NULL
			, `y` TINYINT NOT NULL
			, `is_in_quick` TINYINT NOT NULL
			, CONSTRAINT `CharacterSkill_fk_cid` FOREIGN KEY (`cid`)
				REFERENCES `Character` (`id`)
				ON DELETE CASCADE ON UPDATE CASCADE
		) ENGINE=InnoDB AUTO_INCREMENT=1 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci;
		)delimiter");
		statement.Execute();
	}
	void CharacterSkillTable::DropTable()
	{
		auto statement = _connection.GetStatement();
		statement.Prepare(R"delimiter(
		DROP TABLE IF EXISTS `CharacterSkill`;
		)delimiter");
		statement.Execute();
	}
	void CharacterSkillTable::Add(const cebreiro::gamebase::CharacterSkill& item)
	{
		auto statement = _connection.GetStatement();
		statement.Prepare(R"delimiter(
			INSERT INTO `CharacterSkill`
				(`cid`, `skill_id`, `job`, `level`, `cooldown`, `page`, `x`, `y`, `is_in_quick`)
			VALUES
				(?, ?, ?, ?, ?, ?, ?, ?, ?);
		)delimiter");
		statement.Set<int64_t>(1, item.cid);
		statement.Set<int32_t>(2, item.skill_id);
		statement.Set<int32_t>(3, item.job);
		statement.Set<int32_t>(4, item.level);
		statement.Set<int32_t>(5, item.cooldown);
		statement.Set<int8_t>(6, item.page);
		statement.Set<int8_t>(7, item.x);
		statement.Set<int8_t>(8, item.y);
		statement.Set<int8_t>(9, item.is_in_quick);
		statement.Execute();
	}
	void CharacterSkillTable::Assign(const cebreiro::gamebase::CharacterSkill& item)
	{
		auto statement = _connection.GetStatement();
		statement.Prepare(R"delimiter(
			INSERT INTO `CharacterSkill`
				(`cid`, `skill_id`, `job`, `level`, `cooldown`, `page`, `x`, `y`, `is_in_quick`)
			VALUES
				(?, ?, ?, ?, ?, ?, ?, ?, ?)
			ON DUPLICATE KEY UPDATE
				(`skill_id` = ?, `job` = ?, `level` = ?, `cooldown` = ?, `page` = ?, `x` = ?, `y` = ?, `is_in_quick` = ?);
		)delimiter");
		statement.Set<int64_t>(1, item.cid);
		statement.Set<int32_t>(2, item.skill_id);
		statement.Set<int32_t>(3, item.job);
		statement.Set<int32_t>(4, item.level);
		statement.Set<int32_t>(5, item.cooldown);
		statement.Set<int8_t>(6, item.page);
		statement.Set<int8_t>(7, item.x);
		statement.Set<int8_t>(8, item.y);
		statement.Set<int8_t>(9, item.is_in_quick);
		statement.Set<int32_t>(10, item.skill_id);
		statement.Set<int32_t>(11, item.job);
		statement.Set<int32_t>(12, item.level);
		statement.Set<int32_t>(13, item.cooldown);
		statement.Set<int8_t>(14, item.page);
		statement.Set<int8_t>(15, item.x);
		statement.Set<int8_t>(16, item.y);
		statement.Set<int8_t>(17, item.is_in_quick);
		statement.Execute();
	}
	void CharacterSkillTable::RemoveByCID(const int64_t& cid)
	{
		auto statement = _connection.GetStatement();
		statement.Prepare(R"delimiter(
			DELETE FROM `CharacterSkill`
				WHERE `cid` = ?;
			
		)delimiter");
		
		statement.Set<int64_t>(1, cid);
		statement.Execute();
	}
	auto CharacterSkillTable::FindByCID(const int64_t& cid) -> std::vector<cebreiro::gamebase::CharacterSkill>
	{
		auto statement = _connection.GetStatement();
		statement.Prepare(R"delimiter(
			SELECT * FROM `CharacterSkill`
				WHERE `cid` = ?;
			
		)delimiter");
		
		statement.Set<int64_t>(1, cid);
		statement.Execute();

		std::vector<cebreiro::gamebase::CharacterSkill> result;
		auto resultSet = statement.GetResultSet();
		while (resultSet.Fetch())
		{
			result.push_back(Deserializer<cebreiro::gamebase::CharacterSkill>::Deserialize(resultSet));
		}
		return result;
	}
	auto CharacterSkillTable::GetAll() -> std::vector<cebreiro::gamebase::CharacterSkill>
	{
		auto statement = _connection.GetStatement();
		statement.Prepare(R"delimiter(
			SELECT * FROM `CharacterSkill`
			
		)delimiter");
		
		statement.Execute();

		std::vector<cebreiro::gamebase::CharacterSkill> result;
		auto resultSet = statement.GetResultSet();
		while (resultSet.Fetch())
		{
			result.push_back(Deserializer<cebreiro::gamebase::CharacterSkill>::Deserialize(resultSet));
		}
		return result;
	}
}

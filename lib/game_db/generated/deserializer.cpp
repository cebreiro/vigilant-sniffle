#include "deserializer.h"

#include <cstdint>
#include <cassert>
#include <format>

#include "lib/game_base/db/account.h"
#include "lib/game_base/db/character.h"

namespace cebreiro::gamedb
{
	auto Deserializer<cebreiro::gamebase::Account>::Deserialize(odbc::ResultSet& rs) -> cebreiro::gamebase::Account
	{
		cebreiro::gamebase::Account result;
		result.id = rs.GetInt64(1);
		result.account = rs.GetString(2);
		result.password = rs.GetString(3);
		result.gm_level = rs.GetInt8(4);
		if (rs.IsNull(5))
		{
			result.banned = std::nullopt;
		}
		else
		{
			result.banned = rs.GetInt8(5);
		}
		if (rs.IsNull(6))
		{
			result.ban_reason = std::nullopt;
		}
		else
		{
			result.ban_reason = rs.GetString(6);
		}

		return result;
	}
	auto Deserializer<cebreiro::gamebase::Character>::Deserialize(odbc::ResultSet& rs) -> cebreiro::gamebase::Character
	{
		cebreiro::gamebase::Character result;
		result.id = rs.GetInt64(1);
		result.aid = rs.GetInt64(2);
		result.wid = rs.GetInt8(3);
		result.slot = rs.GetInt8(4);
		result.name = rs.GetString(5);
		result.hair_color = rs.GetInt32(6);
		result.hair = rs.GetInt32(7);
		result.skin_color = rs.GetInt32(8);
		result.face = rs.GetInt32(9);
		result.arms = rs.GetInt8(10);
		result.running = rs.GetInt8(11);
		result.gold = rs.GetInt32(12);
		result.inventory_page = rs.GetInt8(13);
		result.zone = rs.GetInt32(14);
		result.stage = rs.GetInt32(15);
		result.x = rs.GetFloat32(16);
		result.y = rs.GetFloat32(17);

		return result;
	}
	auto Deserializer<cebreiro::gamebase::CharacterStat>::Deserialize(odbc::ResultSet& rs) -> cebreiro::gamebase::CharacterStat
	{
		cebreiro::gamebase::CharacterStat result;
		result.cid = rs.GetInt64(1);
		result.gender = rs.GetInt8(2);
		result.hp = rs.GetInt32(3);
		result.mp = rs.GetInt32(4);
		result.chr_lv = rs.GetInt32(5);
		result.chr_exp = rs.GetInt32(6);
		result.str = rs.GetInt32(7);
		result.dex = rs.GetInt32(8);
		result.accr = rs.GetInt32(9);
		result.health = rs.GetInt32(10);
		result.intell = rs.GetInt32(11);
		result.wis = rs.GetInt32(12);
		result.will = rs.GetInt32(13);
		result.stat_point = rs.GetInt32(14);
		result.water = rs.GetInt8(15);
		result.fire = rs.GetInt8(16);
		result.lightning = rs.GetInt8(17);

		return result;
	}
	auto Deserializer<cebreiro::gamebase::CharacterJob>::Deserialize(odbc::ResultSet& rs) -> cebreiro::gamebase::CharacterJob
	{
		cebreiro::gamebase::CharacterJob result;
		result.cid = rs.GetInt64(1);
		result.job1 = rs.GetInt32(2);
		result.job1_level = rs.GetInt32(3);
		result.job1_exp = rs.GetInt32(4);
		result.job1_sp = rs.GetInt32(5);
		result.job2 = rs.GetInt32(6);
		result.job2_level = rs.GetInt32(7);
		result.job2_exp = rs.GetInt32(8);
		result.job2_sp = rs.GetInt32(9);
		result.job3 = rs.GetInt32(10);
		result.job3_level = rs.GetInt32(11);
		result.job3_exp = rs.GetInt32(12);
		result.job3_sp = rs.GetInt32(13);
		result.job_sub = rs.GetInt32(14);
		result.job_sub_level = rs.GetInt32(15);
		result.job_sub_exp = rs.GetInt32(16);
		result.job_sub_sp = rs.GetInt32(17);

		return result;
	}
	auto Deserializer<cebreiro::gamebase::CharacterItem>::Deserialize(odbc::ResultSet& rs) -> cebreiro::gamebase::CharacterItem
	{
		cebreiro::gamebase::CharacterItem result;
		result.id = rs.GetInt64(1);
		result.cid = rs.GetInt64(2);
		result.item_id = rs.GetInt32(3);
		result.quantity = rs.GetInt32(4);
		result.equip_position = rs.GetInt8(5);
		result.page = rs.GetInt8(6);
		result.x = rs.GetInt8(7);
		result.y = rs.GetInt8(8);
		result.is_in_quick = rs.GetInt8(9);
		result.is_pick = rs.GetInt8(10);

		return result;
	}
	auto Deserializer<cebreiro::gamebase::CharacterSkill>::Deserialize(odbc::ResultSet& rs) -> cebreiro::gamebase::CharacterSkill
	{
		cebreiro::gamebase::CharacterSkill result;
		result.cid = rs.GetInt64(1);
		result.skill_id = rs.GetInt32(2);
		result.job = rs.GetInt32(3);
		result.level = rs.GetInt32(4);
		result.cooldown = rs.GetInt32(5);
		result.page = rs.GetInt8(6);
		result.x = rs.GetInt8(7);
		result.y = rs.GetInt8(8);
		result.is_in_quick = rs.GetInt8(9);

		return result;
	}
}

#pragma once
#include <cstdint>
#include <memory>

#include "lib/odbc/connection.h"

namespace cebreiro::gamebase { struct Account; } 
namespace cebreiro::gamebase { struct Character; } 
namespace cebreiro::gamebase { struct CharacterStat; } 
namespace cebreiro::gamebase { struct CharacterJob; } 
namespace cebreiro::gamebase { struct CharacterItem; } 
namespace cebreiro::gamebase { struct CharacterSkill; } 
namespace cebreiro::gamedb
{
	template <typename T> struct Deserializer;

	template <> struct Deserializer<cebreiro::gamebase::Account> {
		static auto Deserialize(odbc::ResultSet& rs) -> cebreiro::gamebase::Account;
	};
	template <> struct Deserializer<cebreiro::gamebase::Character> {
		static auto Deserialize(odbc::ResultSet& rs) -> cebreiro::gamebase::Character;
	};
	template <> struct Deserializer<cebreiro::gamebase::CharacterStat> {
		static auto Deserialize(odbc::ResultSet& rs) -> cebreiro::gamebase::CharacterStat;
	};
	template <> struct Deserializer<cebreiro::gamebase::CharacterJob> {
		static auto Deserialize(odbc::ResultSet& rs) -> cebreiro::gamebase::CharacterJob;
	};
	template <> struct Deserializer<cebreiro::gamebase::CharacterItem> {
		static auto Deserialize(odbc::ResultSet& rs) -> cebreiro::gamebase::CharacterItem;
	};
	template <> struct Deserializer<cebreiro::gamebase::CharacterSkill> {
		static auto Deserialize(odbc::ResultSet& rs) -> cebreiro::gamebase::CharacterSkill;
	};
}

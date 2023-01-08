#pragma once
#include <cstdint>
#include <memory>
#include <vector>

#include "lib/game_base/db/character.h"

namespace cebreiro::odbc { class Connection; }

namespace cebreiro::gamedb
{
	class CharacterTable
	{
	public:
		CharacterTable(odbc::Connection& connection);

		void CreateTable();
		void DropTable();

		void Add(const cebreiro::gamebase::Character& item);
		void Assign(const cebreiro::gamebase::Character& item);

		void RemoveByID(const int64_t& id);
		void RemoveByAID(const int64_t& aid);

		auto FindByID(const int64_t& id) -> std::optional<cebreiro::gamebase::Character>;
		auto FindByNAME(const std::string& name) -> std::optional<cebreiro::gamebase::Character>;
		auto FindByAID(const int64_t& aid) -> std::vector<cebreiro::gamebase::Character>;

		auto GetAll() -> std::vector<cebreiro::gamebase::Character>;

	private:
		odbc::Connection& _connection;
	};

	class CharacterStatTable
	{
	public:
		CharacterStatTable(odbc::Connection& connection);

		void CreateTable();
		void DropTable();

		void Add(const cebreiro::gamebase::CharacterStat& item);
		void Assign(const cebreiro::gamebase::CharacterStat& item);

		void RemoveByCID(const int64_t& cid);

		auto FindByCID(const int64_t& cid) -> std::optional<cebreiro::gamebase::CharacterStat>;

		auto GetAll() -> std::vector<cebreiro::gamebase::CharacterStat>;

	private:
		odbc::Connection& _connection;
	};

	class CharacterJobTable
	{
	public:
		CharacterJobTable(odbc::Connection& connection);

		void CreateTable();
		void DropTable();

		void Add(const cebreiro::gamebase::CharacterJob& item);
		void Assign(const cebreiro::gamebase::CharacterJob& item);

		void RemoveByCID(const int64_t& cid);

		auto FindByCID(const int64_t& cid) -> std::optional<cebreiro::gamebase::CharacterJob>;

		auto GetAll() -> std::vector<cebreiro::gamebase::CharacterJob>;

	private:
		odbc::Connection& _connection;
	};

	class CharacterItemTable
	{
	public:
		CharacterItemTable(odbc::Connection& connection);

		void CreateTable();
		void DropTable();

		void Add(const cebreiro::gamebase::CharacterItem& item);
		void Assign(const cebreiro::gamebase::CharacterItem& item);

		void RemoveByID(const int64_t& id);
		void RemoveByCID(const int64_t& cid);

		auto FindByID(const int64_t& id) -> std::optional<cebreiro::gamebase::CharacterItem>;
		auto FindByCID(const int64_t& cid) -> std::vector<cebreiro::gamebase::CharacterItem>;

		auto GetAll() -> std::vector<cebreiro::gamebase::CharacterItem>;

	private:
		odbc::Connection& _connection;
	};

	class CharacterSkillTable
	{
	public:
		CharacterSkillTable(odbc::Connection& connection);

		void CreateTable();
		void DropTable();

		void Add(const cebreiro::gamebase::CharacterSkill& item);
		void Assign(const cebreiro::gamebase::CharacterSkill& item);

		void RemoveByCID(const int64_t& cid);

		auto FindByCID(const int64_t& cid) -> std::vector<cebreiro::gamebase::CharacterSkill>;

		auto GetAll() -> std::vector<cebreiro::gamebase::CharacterSkill>;

	private:
		odbc::Connection& _connection;
	};

}

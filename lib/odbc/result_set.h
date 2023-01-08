#pragma once
#include <cstdint>
#include <string>
#include "lib/odbc/odbc_include.h"

namespace cebreiro::odbc
{
	class Statement;

	class ResultSet
	{
	public:
		ResultSet(const Statement& statement);
		~ResultSet();

		bool Fetch();
		bool Next();

		bool IsNull(int32_t index);
		auto GetInt8(int32_t index) -> int8_t;
		auto GetUInt8(int32_t index) -> uint8_t;
		auto GetInt16(int32_t index) -> int16_t;
		auto GetUInt16(int32_t index) -> uint16_t;
		auto GetInt32(int32_t index) -> int32_t;
		auto GetUInt32(int32_t index) -> uint32_t;
		auto GetInt64(int32_t index) -> int64_t;
		auto GetFloat32(int32_t index) -> float;
		auto GetFloat64(int32_t index) -> double;
		auto GetString(int32_t index) -> std::string;

	private:
		SQLHSTMT _handle = nullptr;
	};
}
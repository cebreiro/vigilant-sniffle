#pragma once
#include <cstdint>
#include <string>
#include <optional>
#include "lib/common/type_util.h"
#include "lib/odbc/odbc_include.h"
#include "lib/odbc/result_set.h"

namespace cebreiro::odbc
{
	class Connection;

	class Statement
	{
		friend class ResultSet;

	public:
		Statement() = default;
		Statement(Statement&& rhs) noexcept;
		Statement& operator=(Statement&& rhs) noexcept;

		explicit Statement(const Connection& connection);
		~Statement();

		void Prepare(std::string query);
		void Execute();

		auto GetResultSet() -> ResultSet;

		void SetNull(int32_t index);
		void SetInt8(int32_t index, const int8_t& value);
		void SetUInt8(int32_t index, const uint8_t& value);
		void SetInt16(int32_t index, const int16_t& value);
		void SetUInt16(int32_t index, const uint16_t& value);
		void SetInt32(int32_t index, const int32_t& value);
		void SetUInt32(int32_t index, const uint32_t& value);
		void SetInt64(int32_t index, const int64_t& value);
		void SetFloat32(int32_t index, const float& value);
		void SetFloat64(int32_t index, const double& value);
		void SetString(int32_t index, const std::string& value);

		template <typename T>
		void Set(int32_t index, const T& value);

	private:
		SQLHSTMT _handle = nullptr;


	};

	template <typename T>
	void Statement::Set(int32_t index, const T& value)
	{
		if constexpr (IsOptional<T>::value)
		{
			if (value.has_value())
			{
				Set(index, value.value());
			}
			else
			{
				SetNull(index);
			}
		}
		else if constexpr (std::is_same_v<T, int8_t>)
		{
			SetInt8(index, value);
		}
		else if constexpr (std::is_same_v<T, uint8_t>)
		{
			SetUInt8(index, value);
		}
		else if constexpr (std::is_same_v<T, int16_t>)
		{
			SetInt16(index, value);
		}
		else if constexpr (std::is_same_v<T, uint16_t>)
		{
			SetUInt16(index, value);
		}
		else if constexpr (std::is_same_v<T, int32_t>)
		{
			SetInt32(index, value);
		}
		else if constexpr (std::is_same_v<T, uint32_t>)
		{
			SetUInt32(index, value);
		}
		else if constexpr (std::is_same_v<T, int64_t>)
		{
			SetInt64(index, value);
		}
		else if constexpr (std::is_same_v<T, uint64_t>)
		{
			SetUInt64(index, value);
		}
		else if constexpr (std::is_same_v<T, float>)
		{
			SetFloat32(index, value);
		}
		else if constexpr (std::is_same_v<T, double>)
		{
			SetFloat64(index, value);
		}
		else if constexpr (std::is_same_v<T, std::string>)
		{
			SetString(index, value);
		}
		else
		{
			static_assert(!sizeof(T), "not implement");
		}
	}
}
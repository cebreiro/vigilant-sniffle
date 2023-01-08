#pragma once
#include <cstdint>

namespace cebreiro::gamebase
{
	enum class SerializedType : uint8_t
	{
		Int8 = 1,
		Int16 = 2,
		Int32 = 3,
		Float = 4,
		String = 7,
		Object = 0x80,
	};

	template <typename T>
	struct Serialized;

	template <>
	struct Serialized<int8_t>
	{
		static constexpr SerializedType TYPE = SerializedType::Int8;
	};

	template <>
	struct Serialized<int16_t>
	{
		static constexpr SerializedType TYPE = SerializedType::Int16;
	};

	template <>
	struct Serialized<int32_t>
	{
		static constexpr SerializedType TYPE = SerializedType::Int32;
	};

	template <>
	struct Serialized<float>
	{
		static constexpr SerializedType TYPE = SerializedType::Float;
	};

	template <>
	struct Serialized<std::string>
	{
		static constexpr SerializedType TYPE = SerializedType::String;
	};
}
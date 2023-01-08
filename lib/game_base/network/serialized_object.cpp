#include "serialized_object.h"

namespace cebreiro::gamebase
{
	void SerializedObject::WriteInt8(int8_t value)
	{
		Write<decltype(value)>(value);
	}

	void SerializedObject::WriteUInt8(uint8_t value)
	{
		Write<decltype(value)>(value);
	}

	void SerializedObject::WriteInt16(int16_t value)
	{
		Write<decltype(value)>(value);
	}

	void SerializedObject::WriteUInt16(uint16_t value)
	{
		Write<decltype(value)>(value);
	}

	void SerializedObject::WriteInt32(int32_t value)
	{
		Write<decltype(value)>(value);
	}

	void SerializedObject::WriteUInt32(uint32_t value)
	{
		Write<decltype(value)>(value);
	}

	void SerializedObject::WriteFloat32(float value)
	{
		Write<decltype(value)>(value);
	}

	void SerializedObject::WriteBytes(const char* buffer, size_t size)
	{
		ExpandIfOutOfRange(size);

		std::copy_n(buffer, size, std::back_inserter(_buffer));
	}

	void SerializedObject::WriteString(const std::string& str)
	{
		WriteBytes(str.data(), str.length() + 1);
	}

	void SerializedObject::WriteZeroBytes(size_t size)
	{
		char* buffer = static_cast<char*>(::_alloca(size));
		::memset(buffer, 0, size);

		WriteBytes(buffer, size);
	}

	auto SerializedObject::GetData() const -> const char*
	{
		return _buffer.data();
	}

	auto SerializedObject::GetSize() const -> size_t
	{
		return _buffer.size();
	}

	template <typename T>
	auto SerializedObject::Write(T value) -> std::enable_if_t<std::is_arithmetic_v<T>>
	{
		ExpandIfOutOfRange(sizeof(T));

		std::copy_n(reinterpret_cast<const char*>(&value), sizeof(T), std::back_inserter(_buffer));
	}

	void SerializedObject::ExpandIfOutOfRange(size_t size)
	{
		if (_buffer.size() + size > _buffer.capacity())
		{
			_buffer.reserve(_buffer.size() * 2);
		}
	}
}

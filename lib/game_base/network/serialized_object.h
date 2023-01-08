#pragma once
#include <string>
#include <boost/container/small_vector.hpp>

namespace cebreiro::gamebase
{
	class SerializedObject
	{
	public:
		void WriteInt8(int8_t value);
		void WriteUInt8(uint8_t value);
		void WriteInt16(int16_t value);
		void WriteUInt16(uint16_t value);
		void WriteInt32(int32_t value);
		void WriteUInt32(uint32_t value);
		void WriteFloat32(float value);
		void WriteBytes(const char* buffer, size_t size);
		void WriteString(const std::string& str);
		void WriteZeroBytes(size_t size);

		auto GetData() const -> const char*;
		auto GetSize() const -> size_t;

	private:
		template <typename T>
		auto Write(T value) -> std::enable_if_t<std::is_arithmetic_v<T>>;

		void ExpandIfOutOfRange(size_t size);

	private:
		using container_type = boost::container::small_vector<char, 512>;
		container_type _buffer;
	};
}
#pragma once
#include <cstdint>
#include <string>
#include <type_traits>

namespace cebreiro
{
	class ISerializable;

	class StreamWriter
	{
	public:
		StreamWriter() = default;
		StreamWriter(const StreamWriter&) = default;
		StreamWriter& operator=(const StreamWriter&) = default;

		StreamWriter(char* buffer, size_t size, size_t offset = 0);
		~StreamWriter();

		bool CanWrite(size_t size) const noexcept;

		void WriteInt8(int8_t value);
		void WriteUInt8(uint8_t value);
		void WriteInt16(int16_t value);
		void WriteUInt16(uint16_t value);
		void WriteInt32(int32_t value);
		void WriteUInt32(uint32_t value);
		void WriteInt64(int64_t value);
		void WriteUInt64(uint64_t value);
		void WriteFloat32(float value);
		void WriteFloat64(double value);
		void WriteBytes(const char* buffer, size_t size);
		void WriteString(const std::string& str);
		void WriteZeroBytes(size_t size);
		void Write(ISerializable& serializable);

		auto GetData() const noexcept -> const char*;
		auto GetSize() const noexcept -> size_t;
		auto GetOffset() const noexcept -> size_t;

		void SetOffset(size_t offset);

	private:
		template <typename T>
		auto Write(T value) -> std::enable_if_t<std::is_arithmetic_v<T>>;

		template <typename T>
		auto Write(T value, size_t offset) -> std::enable_if_t<std::is_arithmetic_v<T>>;

		void ThrowIfOutOfRange(size_t size);

	private:
		char* _buffer = nullptr;
		size_t _size = 0;
		size_t _offset = 0;
	};
}
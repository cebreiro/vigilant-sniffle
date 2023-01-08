#pragma once
#include <cstdint>
#include <string>
#include <type_traits>

namespace cebreiro
{
	class IDeserializable;

	class StreamReader
	{
	public:
		StreamReader() = default;
		StreamReader(const StreamReader& rhs) = default;
		StreamReader& operator=(const StreamReader& rhs) = default;

		StreamReader(const char* buffer, size_t size, size_t offset = 0);
		~StreamReader();

		bool CanRead(size_t size) const noexcept;

		auto ReadInt8() -> int8_t;
		auto ReadUInt8() -> uint8_t;
		auto ReadInt16() -> int16_t;
		auto ReadUInt16() -> uint16_t;
		auto ReadInt32() -> int32_t;
		auto ReadUInt32() -> uint32_t;
		auto ReadInt64() -> int64_t;
		auto ReadUInt64() -> uint64_t;
		auto ReadFloat32() -> float;
		auto ReadFloat64() -> double;
		auto ReadString() -> std::string;
		auto ReadString(size_t stringSize) -> std::string;
		void Read(char* outBuffer, size_t bufferSize);
		void Read(IDeserializable& deserializable);

		template <typename T>
		auto Read() -> std::enable_if_t<std::is_arithmetic_v<T>, T>;

		void Skip(size_t skipSize);

		auto GetData() const noexcept -> const char*;
		auto GetSize() const noexcept -> size_t;
		auto GetOffset() const noexcept -> size_t;

		void SetOffset(size_t offset);

		void ThrowIfOutOfRange(size_t size);

	private:
		const char* _buffer = nullptr;
		size_t _size = 0;
		size_t _offset = 0;
	};

	template <typename T>
	auto StreamReader::Read() -> std::enable_if_t<std::is_arithmetic_v<T>, T>
	{
		ThrowIfOutOfRange(sizeof(T));

		T result = *reinterpret_cast<const T*>(_buffer + _offset);
		_offset += sizeof(T);

		return result;
	}
}
#include "stream_writer.h"

#include <format>

#include "lib/common/stacktrace_exception.h"
#include "lib/common/stream/serializable.h"

namespace cebreiro
{
	StreamWriter::StreamWriter(char* buffer, size_t size, size_t offset)
		: _buffer(buffer)
		, _size(size)
		, _offset(offset)
	{
	}

	StreamWriter::~StreamWriter()
	{
	}

	bool StreamWriter::CanWrite(size_t size) const noexcept
	{
		return (_offset + size) <= _size;
	}

	void StreamWriter::WriteInt8(int8_t value)
	{
		Write<decltype(value)>(value);
	}

	void StreamWriter::WriteUInt8(uint8_t value)
	{
		Write<decltype(value)>(value);
	}

	void StreamWriter::WriteInt16(int16_t value)
	{
		Write<decltype(value)>(value);
	}

	void StreamWriter::WriteUInt16(uint16_t value)
	{
		Write<decltype(value)>(value);
	}

	void StreamWriter::WriteInt32(int32_t value)
	{
		Write<decltype(value)>(value);
	}

	void StreamWriter::WriteUInt32(uint32_t value)
	{
		Write<decltype(value)>(value);
	}

	void StreamWriter::WriteInt64(int64_t value)
	{
		Write<decltype(value)>(value);
	}

	void StreamWriter::WriteUInt64(uint64_t value)
	{
		Write<decltype(value)>(value);
	}

	void StreamWriter::WriteFloat32(float value)
	{
		Write<decltype(value)>(value);
	}

	void StreamWriter::WriteFloat64(double value)
	{
		Write<decltype(value)>(value);
	}

	void StreamWriter::WriteBytes(const char* buffer, size_t size)
	{
		ThrowIfOutOfRange(size);

		memcpy(_buffer + _offset, buffer, size);
		_offset += size;
	}

	void StreamWriter::WriteString(const std::string& str)
	{
		WriteBytes(str.data(), str.length() + 1);
	}

	void StreamWriter::WriteZeroBytes(size_t size)
	{
		ThrowIfOutOfRange(size);

		memset(_buffer + _offset, 0, size);
		_offset += size;
	}

	void StreamWriter::Write(ISerializable& serializable)
	{
		serializable.Serialize(*this);
	}

	const char* StreamWriter::GetData() const noexcept
	{
		return _buffer;
	}

	size_t StreamWriter::GetSize() const noexcept
	{
		return _size;
	}

	size_t StreamWriter::GetOffset() const noexcept
	{
		return _offset;
	}

	void StreamWriter::SetOffset(size_t offset)
	{
		_offset = offset;
	}

	template <typename T>
	auto StreamWriter::Write(T value) -> std::enable_if_t<std::is_arithmetic_v<T>>
	{
		ThrowIfOutOfRange(sizeof(T));

		*reinterpret_cast<T*>(_buffer + _offset) = value;
		_offset += sizeof(T);
	}

	template <typename T>
	auto StreamWriter::Write(T value, size_t offset) -> std::enable_if_t<std::is_arithmetic_v<T>>
	{
		const size_t current = GetOffset();

		SetOffset(offset);
		Write<T>(value);

		SetOffset(current);
	}

	void StreamWriter::ThrowIfOutOfRange(size_t size)
	{
		if (!CanWrite(size))
		{
			throw StacktraceException(std::format("stream out of range offset: {}, read: {}", _offset, size));
		}
	}
}
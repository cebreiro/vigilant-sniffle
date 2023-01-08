#include "stream_reader.h"

#include <format>
#include <iterator>

#include "lib/common/stacktrace_exception.h"
#include "lib/common/stream/deserializable.h"
#include "lib/common/stream/stream_util.h"

namespace cebreiro
{
	StreamReader::StreamReader(const char* buffer, size_t size, size_t offset)
		: _buffer(buffer)
		, _size(size)
		, _offset(offset)
	{
	}

	StreamReader::~StreamReader()
	{
	}

	bool StreamReader::CanRead(size_t size) const noexcept
	{
		return (_offset + size) <= _size;
	}

	int8_t StreamReader::ReadInt8()
	{
		return Read<int8_t>();
	}

	uint8_t StreamReader::ReadUInt8()
	{
		return Read<uint8_t>();
	}

	int16_t StreamReader::ReadInt16()
	{
		return Read<int16_t>();
	}

	uint16_t StreamReader::ReadUInt16()
	{
		return Read<uint16_t>();
	}

	int32_t StreamReader::ReadInt32()
	{
		return Read<int32_t>();
	}

	uint32_t StreamReader::ReadUInt32()
	{
		return Read<uint32_t>();
	}

	int64_t StreamReader::ReadInt64()
	{
		return Read<int64_t>();
	}

	uint64_t StreamReader::ReadUInt64()
	{
		return Read<uint64_t>();
	}

	float StreamReader::ReadFloat32()
	{
		return Read<float>();
	}

	double StreamReader::ReadFloat64()
	{
		return Read<double>();
	}

	std::string StreamReader::ReadString()
	{
		return ReadString(strlen(_buffer + _offset) + 1);
	}

	std::string StreamReader::ReadString(size_t stringSize)
	{
		ThrowIfOutOfRange(stringSize);

		if (stringSize == 0)
		{
			return "";
		}

		std::string str;
		str.reserve(stringSize + 1);
		std::copy_n(_buffer + _offset, stringSize, std::back_inserter(str));
		str[stringSize] = '\0';

		_offset += stringSize;

		return str;
	}

	void StreamReader::Read(char* outBuffer, size_t bufferSize)
	{
		ThrowIfOutOfRange(bufferSize);

		memcpy(outBuffer, _buffer + _offset, bufferSize);
		_offset += bufferSize;
	}

	void StreamReader::Read(IDeserializable& deserializable)
	{
		deserializable.Deserialize(*this);
	}

	void StreamReader::Skip(size_t skipSize)
	{
		ThrowIfOutOfRange(skipSize);
		_offset += skipSize;
	}

	const char* StreamReader::GetData() const noexcept
	{
		return _buffer;
	}

	size_t StreamReader::GetSize() const noexcept
	{
		return _size;
	}

	size_t StreamReader::GetOffset() const noexcept
	{
		return _offset;
	}

	void StreamReader::SetOffset(size_t offset)
	{
		_offset = offset;
	}

	void StreamReader::ThrowIfOutOfRange(size_t size)
	{
		if (!CanRead(size))
		{
			throw StacktraceException(std::format("stream out of range offset:{} read:{} size: {} bytes:{}",
				_offset, size, _size, ToString(_buffer, _size, 64)));
		}
	}
}

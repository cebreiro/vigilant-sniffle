#include "packet_reader.h"

#include <cassert>
#include <format>

#include "lib/common/stacktrace_exception.h"
#include "lib/common/stream/stream_util.h"
#include "lib/network/buffer.h"
#include "lib/game_base/network/serialized_object_type.h"

namespace cebreiro::gamebase
{
	PacketReader::PacketReader(const network::Buffer& buffer)
		: _reader(buffer.Data(), buffer.Size(), 11)
		, _iter(_offsets.end())
		, _end(_offsets.end())
	{
		if (!HasValidPacketHeader())
		{
			throw StacktraceException(
				std::format("invalid packet header. recv: {}",
					ToString(_reader.GetData(), _reader.GetSize())));
		}

		Parse();
	}

	auto PacketReader::ReadInt8() -> int8_t
	{
		return Read<int8_t>();
	}

	auto PacketReader::ReadInt16() -> int16_t
	{
		return Read<int16_t>();
	}

	auto PacketReader::ReadInt32() -> int32_t
	{
		return Read<int32_t>();
	}

	auto PacketReader::ReadInt64() -> std::pair<int32_t, int32_t>
	{
		if (_iter == _end)
		{
			throw StacktraceException("packet_reader out of range");
		}

		Next();

		constexpr uint8_t expected = 0x81ui8 + 8;
		ThrowIfInvalidPacketType(expected, _reader.ReadUInt8());

		int32_t low = _reader.ReadInt32();
		int32_t high = _reader.ReadInt32();

		return { low, high };
	}

	auto PacketReader::ReadFloat32() -> float
	{
		return Read<float>();
	}

	auto PacketReader::ReadString() -> std::string
	{
		if (_iter == _end)
		{
			throw StacktraceException("packet_reader out of range");
		}

		Next();

		uint8_t type = _reader.ReadUInt8();
		uint16_t size = type == static_cast<uint8_t>(SerializedType::String)
			? _reader.ReadInt16() : type - 8ui8;

		ThrowIfOutOfRange(size);

		return std::string(_reader.GetData() + _reader.GetOffset());
	}

	auto PacketReader::ReadObject() -> StreamReader
	{
		if (_iter == _end)
		{
			throw StacktraceException("packet_reader out of range");
		}

		Next();

		const uint8_t type = _reader.ReadUInt8();
		const uint16_t size = type == static_cast<uint8_t>(SerializedType::Object)
			? _reader.ReadInt16() : (type - 0x81ui8);

		ThrowIfOutOfRange(size);

		return StreamReader(_reader.GetData() + _reader.GetOffset(), size);
	}

	template <typename T>
	auto PacketReader::Read() -> std::enable_if_t<std::is_arithmetic_v<T>&& std::is_signed_v<T>, T>
	{
		if (_iter == _end)
		{
			throw StacktraceException("packet_reader out of range");
		}

		Next();

		constexpr auto expected = static_cast<uint8_t>(Serialized<T>::TYPE);
		ThrowIfInvalidPacketType(expected, _reader.ReadUInt8());

		return _reader.Read<T>();
	}

	bool PacketReader::HasValidPacketHeader() const
	{
		const char* buffer = _reader.GetData();
		size_t size = _reader.GetSize();

		if (size < 11)
		{
			return false;
		}

		if (*reinterpret_cast<const uint32_t*>(buffer) != size)
		{
			return false;
		}

		if (*reinterpret_cast<const uint32_t*>(buffer + 4) != (size - 9))
		{
			return false;
		}

		if (*reinterpret_cast<const uint8_t*>(buffer + 8) != (size & 0xFF) + (size / 0xFF))
		{
			return false;
		}

		if (*reinterpret_cast<const uint16_t*>(buffer + 9) != ((size - 9) & 0xFFFF))
		{
			return false;
		}

		return true;
	}

	void PacketReader::Parse()
	{
		size_t operationSize = _reader.ReadUInt16();

		// client 58DA70h
		for (size_t i = 0; i < operationSize; ++i)
		{
			_offsets.push_back(_reader.GetOffset());
			uint8_t typeValue = _reader.ReadUInt8();
			SerializedType type = static_cast<SerializedType>(typeValue);

			switch (type)
			{
			case SerializedType::Int8:
				_reader.Skip(sizeof(int8_t));
				break;
			case SerializedType::Int16:
				_reader.Skip(sizeof(int16_t));
				break;
			case SerializedType::Int32:
				_reader.Skip(sizeof(int32_t));
				break;
			case SerializedType::Float:
				_reader.Skip(sizeof(float));
				break;
			case SerializedType::String:
			case SerializedType::Object:
				_reader.Skip(_reader.ReadInt16());
				break;
			default:
				if (typeValue > 0x81 && typeValue <= 0xFF)
				{
					_reader.Skip(typeValue - 0x81ui8);
				}
				else if (typeValue > 8 && typeValue <= 0x6E)
				{
					_reader.Skip(typeValue - 8ui8);
				}
				else
				{
					throw StacktraceException(
						std::format("packet_reader found unknown type: {}, recv: {}",
							typeValue, ToString(_reader.GetData(), _reader.GetSize())));
				}
			}
		}

		if (_reader.GetSize() != _reader.GetOffset())
		{
			throw StacktraceException(
				std::format("packet_reader parse error recv: {}", 
					ToString(_reader.GetData(), _reader.GetSize())));
		}

		_iter = _offsets.rbegin();
		_end = _offsets.rend();
	}

	void PacketReader::Next()
	{
		_reader.SetOffset(*_iter);
		++_iter;
	}

	void PacketReader::ThrowIfInvalidPacketType(uint8_t expected, uint8_t result) const
	{
		assert(expected == result);

		if (expected != result)
		{
			throw StacktraceException(
				std::format("packet_reader invalid type read. expected: {}, result: {}",
					expected, result));
		}
	}

	void PacketReader::ThrowIfOutOfRange(size_t size) const
	{
		if (!_reader.CanRead(size))
		{
			throw StacktraceException(
				std::format("packet_reader out of range. requested: {}", size));
		}
	}
}

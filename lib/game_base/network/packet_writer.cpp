#include "packet_writer.h"

#include <numeric>
#include <ranges>

#include "lib/game_base/network/serialized_object.h"
#include "lib/game_base/network/packet_serializable.h"
#include "lib/game_base/network/serialized_object_type.h"

namespace cebreiro::gamebase
{
	void PacketWriter::WriteInt8(int8_t value)
	{
		Write<decltype(value)>(value);
	}

	void PacketWriter::WriteInt16(int16_t value)
	{
		Write<decltype(value)>(value);
	}

	void PacketWriter::WriteInt32(int32_t value)
	{
		Write<decltype(value)>(value);
	}

	void PacketWriter::WriteInt64(int32_t low, int32_t high)
	{
		int64_t value = (static_cast<int64_t>(high) << 32) | low;

		block_t& block = _blocks.emplace_back();

		uint8_t buffer[1 + sizeof(int64_t)] = { 0, };
		buffer[0] = 0x81ui8 + 8ui8;
		*reinterpret_cast<int64_t*>(buffer + 1) = value;

		std::copy_n(buffer, sizeof(buffer), std::back_inserter(block));
	}

	void PacketWriter::WriteFloat32(float value)
	{
		Write<decltype(value)>(value);
	}

	void PacketWriter::WriteString(std::string_view str)
	{
		block_t& block = _blocks.emplace_back();

		size_t size = str.length() + 1;
		if (!str.empty() && str.back() == '\0')
		{
			size -= 1;
		}

		if (size <= 0x6E)
		{
			block.push_back(8ui8 + static_cast<uint8_t>(size));
		}
		else
		{
			block.push_back(static_cast<uint8_t>(SerializedType::String));
			std::copy_n(reinterpret_cast<const uint8_t*>(&size), sizeof(uint16_t), std::back_inserter(block));
		}

		std::copy_n(str.data(), size, std::back_inserter(block));
	}

	void PacketWriter::WriteObject(const char* buffer, size_t length)
	{
		block_t& block = _blocks.emplace_back();

		const auto u16Size = static_cast<uint16_t>(length);

		if (u16Size <= 0x6E)
		{
			block.push_back(0x81ui8 + static_cast<uint8_t>(u16Size));
		}
		else
		{
			block.push_back(static_cast<uint8_t>(SerializedType::Object));
			std::copy_n(reinterpret_cast<const uint8_t*>(&u16Size), sizeof(uint16_t), std::back_inserter(block));
		}

		std::copy_n(buffer, u16Size, std::back_inserter(block));
	}

	void PacketWriter::WriteObject(const SerializedObject& serializedObject)
	{
		WriteObject(serializedObject.GetData(), serializedObject.GetSize());
	}

	void PacketWriter::WriteObject(const IPacketSerializable& object)
	{
		object.Serialize(*this);
	}

	void PacketWriter::WriteZeroByte(size_t n)
	{
		block_t& block = _blocks.emplace_back();

		if (n <= 0x6E)
		{
			block.resize(n + 1, 0);
			block[0] = static_cast<uint8_t>(0x81ui8 + n);
		}
		else
		{
			block.resize(n + 3, 0);
			block[0] = static_cast<uint8_t>(SerializedType::Object);
			*reinterpret_cast<uint16_t*>(block.data() + 1) = static_cast<uint16_t>(n);
		}
	}

	auto PacketWriter::MakeBuffer() const -> network::Buffer
	{
		constexpr size_t headSize = 11 + sizeof(uint16_t);
		uint16_t blockCount = static_cast<uint16_t>(_blocks.size());

		size_t bytesSize = std::accumulate(_blocks.begin(), _blocks.end(), 0ui64, [](size_t size, const block_t& block)
			{
				return block.size() + size;
			});

		size_t packetSize = headSize + bytesSize;
		auto buffer = std::make_shared<char[]>(packetSize);

		WriteHead(buffer.get(), packetSize, blockCount);
		WriteBody(buffer.get(), packetSize, headSize);

		return { std::move(buffer), 0, packetSize };
	}

	template <typename T>
	auto PacketWriter::Write(T value)
		-> std::enable_if_t<std::is_arithmetic_v<T>&& std::is_signed_v<T> && sizeof(T) <= sizeof(int32_t)>
	{
		block_t& block = _blocks.emplace_back();

		uint8_t buffer[1 + sizeof(T)] = { 0, };
		buffer[0] = static_cast<uint8_t>(Serialized<T>::TYPE);
		*reinterpret_cast<T*>(buffer + 1) = value;

		std::copy_n(buffer, sizeof(buffer), std::back_inserter(block));
	}

	void PacketWriter::WriteHead(char* buffer, size_t size, uint16_t blockCount)
	{
		size_t offset = 0;
		*reinterpret_cast<uint32_t*>(buffer + offset) = static_cast<uint32_t>(size);
		offset += sizeof(uint32_t);

		*reinterpret_cast<uint32_t*>(buffer + offset) = static_cast<uint32_t>(size - 9);
		offset += sizeof(uint32_t);

		*reinterpret_cast<uint8_t*>(buffer + offset) = static_cast<uint8_t>((size & 0xFF) + (size / 0xFF));
		offset += sizeof(uint8_t);

		*reinterpret_cast<uint16_t*>(buffer + offset) = static_cast<uint16_t>((size - 9) & 0xFFFF);
		offset += sizeof(uint16_t);

		*reinterpret_cast<uint16_t*>(buffer + offset) = blockCount;
	}

	void PacketWriter::WriteBody(char* buffer, size_t size, size_t index) const
	{
		for (const auto& block : std::ranges::reverse_view(_blocks))
		{
			::memcpy(buffer + index, block.data(), block.size());
			index += block.size();
		}

		(void)size;
		assert(index == size);
	}
}

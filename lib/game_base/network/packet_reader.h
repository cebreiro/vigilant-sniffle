#pragma once
#include <span>
#include <concepts>
#include <boost/container/small_vector.hpp>
#include "lib/common/stream/stream_reader.h"
#include "lib/game_base/network/packet_deserializable.h"

namespace cebreiro::network
{
	class Buffer;
}

namespace cebreiro::gamebase
{
	class PacketReader
	{
	public:
		explicit PacketReader(const std::span<const char>& buffer, size_t offset = 0);
		explicit PacketReader(const network::Buffer& buffer);

		auto ReadInt8() -> int8_t;
		auto ReadInt16() -> int16_t;
		auto ReadInt32() -> int32_t;
		auto ReadInt64() -> std::pair<int32_t, int32_t>;
		auto ReadFloat32() -> float;
		auto ReadString() -> std::string;
		auto ReadObject() -> StreamReader;

		template <typename T> requires std::derived_from<T, IPacketDeserializable>
		auto Read() -> T;

		auto GetDebugString() const -> std::string;

	private:
		template <typename T>
		auto Read() -> std::enable_if_t<std::is_arithmetic_v<T> && std::is_signed_v<T>, T>;

	private:
		bool HasValidPacketHeader() const;

		void Parse();
		void Next();
		void ThrowIfInvalidPacketType(uint8_t expected, uint8_t result) const;
		void ThrowIfOutOfRange(size_t size) const;

	private:
		StreamReader _reader;

		using offset_container_type = boost::container::small_vector<size_t, 16>;
		offset_container_type _offsets;
		size_t index = 0;
	};

	template <typename T> requires std::derived_from<T, IPacketDeserializable>
	auto PacketReader::Read() -> T
	{
		T object = {};
		object.Deserialize(*this);

		return object;
	}
}
#pragma once
#include <string_view>
#include <boost/container/small_vector.hpp>
#include "lib/network/buffer.h"

namespace cebreiro::gamebase
{
	struct IPacketSerializable;
	class SerializedObject;

	class PacketWriter
	{
	public:
		void WriteInt8(int8_t value);
		void WriteInt16(int16_t value);
		void WriteInt32(int32_t value);
		void WriteInt64(int32_t low, int32_t high);
		void WriteFloat32(float value);

		void WriteString(std::string_view str);
		void WriteObject(const char* buffer, size_t length);
		void WriteObject(const SerializedObject& serializedObject);
		void WriteObject(const IPacketSerializable& object);
		void WriteZeroByte(size_t n);

		[[nodiscard]]
		auto MakeBuffer() const -> network::Buffer;

	private:
		template <typename T>
		auto Write(T value) -> std::enable_if_t<std::is_arithmetic_v<T> && std::is_signed_v<T> && sizeof(T) <= sizeof(int32_t)>;

		static void WriteHead(char* buffer, size_t size, uint16_t blockCount);
		void WriteBody(char* buffer, size_t size, size_t index) const;

	private:
		using block_t = boost::container::small_vector<uint8_t, 64>;
		boost::container::small_vector<block_t, 16> _blocks;
	};
}

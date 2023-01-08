#include "gateway_packet_decoder.h"

#include "config/server_constant.h"

namespace cebreiro::gateway
{
	static inline constexpr size_t HEAD_SIZE = 15;

	auto GatewayPacketDecoder::GetPacketSize(const std::span<const char>& buffer) const
		-> std::expected<size_t, DecodeError>
	{
		if (buffer.size() < HEAD_SIZE)
		{
			return std::unexpected(DecodeError::ErrorShortLength);
		}

		int32_t length = *reinterpret_cast<const int32_t*>(buffer.data());
		DecodeBuffer(reinterpret_cast<char*>(&length), sizeof(length));

		if (buffer.size() < length)
		{
			return std::unexpected(DecodeError::ErrorShortLength);
		}

		return length;
	}

	void GatewayPacketDecoder::Decode(const std::span<char>& buffer)
	{
		DecodeBuffer(buffer.data(), static_cast<int32_t>(buffer.size()));
		AddIndex(static_cast<int32_t>(buffer.size()));
	}

	void GatewayPacketDecoder::DecodeBuffer(char* buffer, int32_t size) const
	{
		char prev = 0;

		for (int32_t i = 0; i < size; ++i)
		{
			buffer[i] = (buffer[i] ^ static_cast<char>(ServerConstant::CRYPTO_TABLE[(i + _index) & 0xFF])) - prev;
			prev = buffer[i];
		}
	}

	void GatewayPacketDecoder::AddIndex(int32_t value)
	{
		_index += value;
	}
}

#include "zone_packet_decoder.h"

#include "config/server_constant.h"

namespace cebreiro
{
	static inline constexpr size_t HEAD_SIZE = 15;

	auto ZonePacketDecoder::GetPacketSize(const std::span<const char>& buffer) const
		-> std::expected<size_t, DecodeError>
	{
		if (buffer.size() < HEAD_SIZE)
		{
			return std::unexpected(DecodeError::ErrorShortLength);
		}

		int32_t length = *reinterpret_cast<const int32_t*>(buffer.data());
		DecodeBuffer(reinterpret_cast<char*>(&length), sizeof(length), _lastValue);

		if (length <= 0)
		{
			return std::unexpected(DecodeError::ErrorInvalidHead);
		}

		if (buffer.size() < static_cast<size_t>(length))
		{
			return std::unexpected(DecodeError::ErrorShortLength);
		}

		return length;
	}

	void ZonePacketDecoder::Decode(const std::span<char>& buffer)
	{
		DecodeBuffer(buffer.data(), static_cast<int32_t>(buffer.size()), _lastValue);
		AddIndex(static_cast<int32_t>(buffer.size()));
		_lastValue = buffer.back();
	}

	void ZonePacketDecoder::DecodeBuffer(char* buffer, int32_t size, int8_t lastValue) const
	{
		char prev = lastValue;

		for (int64_t i = 0; i < size; ++i)
		{
			buffer[i] = (buffer[i] ^ static_cast<char>(ServerConstant::CRYPTO_TABLE[(i + _index) & 0xFF])) - prev;
			prev = buffer[i];
		}
	}

	void ZonePacketDecoder::AddIndex(int32_t value)
	{
		_index += value;
	}
}

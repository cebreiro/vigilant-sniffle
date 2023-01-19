#include "zone_packet_encoder.h"

#include "config/server_constant.h"

namespace cebreiro
{
	void ZonePacketEncoder::Encode(const std::span<char>& buffer)
	{
		char temp1 = 0;
		char temp2 = _lastValue;

		for (size_t i = 0; i < buffer.size(); ++i)
		{
			temp1 = buffer[i];
			buffer[i] = (temp2 + buffer[i]) ^ static_cast<char>(ServerConstant::CRYPTO_TABLE[(i + _index) & 0xFF]);
			temp2 = temp1;
		}

		_index += static_cast<int32_t>((buffer.size() & 0xFF));
		_lastValue = buffer.back();
	}
}

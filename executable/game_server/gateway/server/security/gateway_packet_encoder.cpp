#include "gateway_packet_encoder.h"

#include "config/server_constant.h"

namespace cebreiro::gateway
{
	void GatewayPacketEncoder::Encode(const std::span<char>& buffer)
	{
		char CL = 0;
		char BL = buffer[0];

		buffer[0] = buffer[0] ^ static_cast<char>(ServerConstant::CRYPTO_TABLE[0 + (_index & 0xFF)]);

		for (int i = 1; i < buffer.size(); ++i)
		{
			CL = buffer[i];
			CL = CL + BL;
			BL = buffer[i];
			buffer[i] = CL ^ static_cast<char>(ServerConstant::CRYPTO_TABLE[(i + _index) & 0xFF]);
		}

		_index += static_cast<int32_t>(buffer.size() & 0xFF);
	}
}

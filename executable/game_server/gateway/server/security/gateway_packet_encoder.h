#pragma once
#include "lib/network/encoder.h"

namespace cebreiro::gateway
{
	class GatewayPacketEncoder : public network::Encoder
	{
	public:
		void Encode(const std::span<char>& buffer) override;

	private:
		int32_t _index = 0;
	};
}
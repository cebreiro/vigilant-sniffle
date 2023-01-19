#pragma once
#include "lib/network/encoder.h"

namespace cebreiro
{
	class ZonePacketEncoder : public network::Encoder
	{
	public:
		void Encode(const std::span<char>& buffer) override;

	private:
		int32_t _index = 0;
		int8_t _lastValue = 0;
	};
}

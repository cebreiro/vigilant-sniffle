#pragma once
#include "lib/network/encoder.h"

namespace cebreiro::login
{
	class LoginPacketEncoder : public network::Encoder
	{
	public:
		LoginPacketEncoder(uint32_t key1, uint32_t key2);

		void Encode(const std::span<char>& buffer) override;

	private:
		std::array<uint32_t, 2> _keys;
	};
}
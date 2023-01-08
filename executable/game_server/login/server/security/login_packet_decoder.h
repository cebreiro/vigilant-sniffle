#pragma once
#include "lib/network/decoder.h"

namespace cebreiro::login
{
	class LoginPacketDecoder : public network::Decoder
	{
	public:
		LoginPacketDecoder(uint32_t key1, uint32_t key2);

		auto GetPacketSize(const std::span<const char>& buffer) const -> std::expected<size_t, DecodeError> override;
		void Decode(const std::span<char>& buffer) override;

	private:
		std::array<uint32_t, 2> _keys;
	};
}
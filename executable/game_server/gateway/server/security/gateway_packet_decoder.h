#pragma once
#include "lib/network/decoder.h"

namespace cebreiro::gateway
{
	class GatewayPacketDecoder : public network::Decoder
	{
	public:
		auto GetPacketSize(const std::span<const char>& buffer) const -> std::expected<size_t, DecodeError> override;
		void Decode(const std::span<char>& buffer) override;

	private:
		void DecodeBuffer(char* buffer, int32_t size) const;
		void AddIndex(int32_t value);

	private:
		int32_t _index = 0;
	};
}
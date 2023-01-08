#pragma once
#include "lib/network/decoder.h"
#include "lib/network/encoder.h"

struct TestDecoder : cebreiro::network::Decoder
{
	auto GetPacketSize(const std::span<const char>& buffer) const->std::expected<size_t, DecodeError> override;
	void Decode(const std::span<char>& buffer) override;
};

struct TestEncoder : cebreiro::network::Encoder
{
	void Encode(const std::span<char>& buffer) override;
};
#include "test_decoder_encoder.h"

auto TestDecoder::GetPacketSize(
	const std::span<const char>& buffer) const -> std::expected<size_t, DecodeError>
{
	if (buffer.empty())
	{
		return std::unexpected(DecodeError::ErrorShortLength);
	}

	return buffer.size();
}

void TestDecoder::Decode(const std::span<char>& buffer)
{
	(void)buffer;
}

void TestEncoder::Encode(const std::span<char>& buffer)
{
	(void)buffer;
}
#pragma once
#include <span>
#include <optional>
#include <expected>

namespace cebreiro::network
{
	class Decoder
	{
	public:
		enum class DecodeError
		{
			ErrorShortLength,
			ErrorInvalidHead,
		};

	public:
		virtual ~Decoder() = default;

		virtual auto GetPacketSize(const std::span<const char>& buffer) const
			-> std::expected<size_t, DecodeError> = 0;
		virtual void Decode(const std::span<char>& buffer) = 0;
	};
}
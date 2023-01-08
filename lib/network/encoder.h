#pragma once
#include <span>

namespace cebreiro::network
{
	class Encoder
	{
	public:
		virtual ~Encoder() = default;

		virtual void Encode(const std::span<char>& buffer) = 0;
	};
}
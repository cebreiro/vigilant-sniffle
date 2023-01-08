#pragma once
#include <cstdint>
#include <string_view>

namespace cebreiro::network
{
	auto AddressToBinaryForm(std::string_view address) -> int32_t;
}
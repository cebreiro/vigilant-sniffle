#pragma once
#include <string>
#include <optional>

namespace cebreiro
{
	auto ToString(const char* buffer, size_t size, std::optional<size_t> maxSize = std::nullopt) -> std::string;
}
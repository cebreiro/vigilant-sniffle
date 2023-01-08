#pragma once
#include <cstdint>
#include <vector>
#include <filesystem>

namespace cebreiro
{
	auto ReadFile(const std::filesystem::path& filePath) -> std::vector<char>;
}
#pragma once
#include <chrono>
#include <filesystem>
#include <ranges>

namespace fs = std::filesystem;
namespace sr = std::ranges;
namespace srv = std::ranges::views;

namespace cebreiro
{
	// intended
	using clock_t = std::chrono::system_clock;
	using time_point_t = clock_t::time_point;
}

#ifdef _DEBUG
#define verify(exp) assert(exp)
#else
#define verify(exp) (void)exp
#endif
	
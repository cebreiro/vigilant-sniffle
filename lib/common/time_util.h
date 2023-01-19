#pragma once
#include <cstdint>
#include <chrono>
#include <string>

#include "lib/common/global.h"

namespace cebreiro
{
	auto Now() -> uint64_t;
	auto ToString(const time_point_t& tp, const char* format = "%Y-%m-%d %H:%M:%S") -> std::string;
	auto ToDate(const time_point_t& tp) -> std::string;
	auto ToDateTime(const time_point_t& tp) -> std::string;
	auto ToDateTimeMilli(const time_point_t& tp) -> std::string;
	auto Count(const time_point_t& tp) -> uint64_t;

	auto GetElapsedTimeMilli(const time_point_t& start, const time_point_t& end = clock_t::now()) -> uint64_t;
}
#include "time_util.h"

#include <cassert>
#include <format>

namespace cebreiro
{
	auto Now() -> uint64_t
	{
		return Count(clock_t::now());
	}

	auto ToString(const time_point_t& tp, const char* format) -> std::string
	{
		auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(tp.time_since_epoch());
		std::time_t t = clock_t::to_time_t(tp);

		std::tm tm = {};
		[[maybe_unused]] errno_t err = localtime_s(&tm, &t);
		assert(err == 0);

		std::ostringstream oss;
		oss << std::put_time(&tm, format);

		return oss.str();
	}

	auto ToDate(const time_point_t& tp) -> std::string
	{
		return ToString(tp, "%Y-%m-%d");
	}

	auto ToDateTime(const time_point_t& tp) -> std::string
	{
		return ToString(tp, "%Y-%m-%d %H:%M:%S");
	}

	auto ToDateTimeMilli(const time_point_t& tp) -> std::string
	{
		auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(tp.time_since_epoch());
		size_t millisecond = ms.count() % 1000;

		auto dateTime = ToDateTime(tp);
		

		if (millisecond <= 9)
		{
			dateTime += std::format(".00{}", millisecond);
		}
		else if (millisecond >= 10 && millisecond <= 99)
		{
			dateTime += std::format(".0{}", millisecond);
		}
		else
		{
			dateTime += std::format(".{}", millisecond);
		}

		return dateTime;
	}

	auto Count(const time_point_t& tp) -> uint64_t
	{
		using namespace std::chrono;

		return time_point_cast<milliseconds>(tp).time_since_epoch().count();
	}

	auto GetElapsedTimeMilli(const time_point_t& start, const time_point_t& end) -> uint64_t
	{
		using std::chrono::milliseconds;
		using std::chrono::duration_cast;
		using std::chrono::duration;
		using std::milli;

		return duration_cast<duration<int64_t, milli>>(end - start).count();
	}
}

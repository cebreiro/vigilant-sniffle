#include "stream_util.h"

#include <sstream>
#include <iomanip>

namespace cebreiro
{
	auto ToString(const char* buffer, size_t size, std::optional<size_t> maxSize) -> std::string
	{
		std::ostringstream oss;
		oss << std::uppercase;
		oss << std::hex;

		int32_t temp = 0;
		for (size_t i = 0; i < size; ++i)
		{
			temp = buffer[i] & 0xFF;
			if (temp >= 0 && temp <= 0xF)
			{
				oss << '0';
			}

			oss << temp;

			if (i != (size - 1))
			{
				oss << " ";
			}

			if (maxSize.has_value() && i >= maxSize)
			{
				break;
			}
		}

		return oss.str();
	}
}

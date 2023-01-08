#pragma once
#include <string>
#include <source_location>
#include "lib/common/log/log_level.h"

namespace cebreiro
{
	class ILogService
	{
	public:
		virtual ~ILogService() {}

		virtual void Log(LogLevel level, const std::string& message, 
			const std::source_location& location = std::source_location::current()) = 0;
	};

	namespace log
	{
		void SetGlobal(ILogService* service);
		auto Global() -> ILogService*;
	}
}
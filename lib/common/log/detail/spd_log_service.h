#pragma once
#include <cstdint>
#include <memory>
#include <optional>
#include "lib/common/log/log_service.h"

namespace cebreiro
{
	struct SpdLogServiceConstructParam
	{
		struct Console
		{
			bool async = false;
			LogLevel level = LogLevel::Debug;
		};
		std::optional<Console> console = std::nullopt;

		struct DailyFile
		{
			std::string path;
			LogLevel level = LogLevel::Debug;
		};
		std::optional<DailyFile> dailyFile = std::nullopt;
	};

	class SpdLogService : public ILogService
	{
		class Impl;

	public:
		explicit SpdLogService(const SpdLogServiceConstructParam& param);
		~SpdLogService() override;

		void Log(LogLevel level, const std::string& message, const std::source_location& location) override;

	private:
		std::shared_ptr<Impl> _impl;
	};
}
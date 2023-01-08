#include "spd_log_service.h"

#include <cassert>
#include <vector>
#include <mutex>
#include <optional>
#include <format>

#include "spdlog/spdlog.h"
#include "spdlog/async.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/daily_file_sink.h"

namespace cebreiro
{
	class SpdLogService::Impl
	{
	public:
		Impl(const SpdLogServiceConstructParam& param)
		{
			LogLevel minSyncLogLevel = LogLevel::Critical;
			std::vector<spdlog::sink_ptr> syncSinks;

			LogLevel minAsyncLogLevel = LogLevel::Critical;
			std::vector<spdlog::sink_ptr> asyncSinks;

			if (param.console)
			{
				auto sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
				sink->set_level(ToSpdLog(param.console->level));
				sink->set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%^%l%$] [%s:%#] [%!] %v");

				if (param.console->async)
				{
					minAsyncLogLevel = std::min(param.console->level, minAsyncLogLevel);
					asyncSinks.push_back(std::move(sink));
				}
				else
				{
					minSyncLogLevel = std::min(param.console->level, minSyncLogLevel);
					syncSinks.push_back(std::move(sink));
				}
			}

			if (param.dailyFile)
			{
				constexpr int32_t rotationHour = 0;
				constexpr int32_t rotationMinute = 0;
				constexpr bool truncate = false;

				auto sink = std::make_shared<spdlog::sinks::daily_file_sink_mt>(
					param.dailyFile->path,
					rotationHour, rotationMinute, truncate);
				sink->set_level(ToSpdLog(param.dailyFile->level));
				sink->set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%l] [%s:%#] [%!] %v");

				asyncSinks.push_back(std::move(sink));
				minAsyncLogLevel = std::min(param.dailyFile->level, minAsyncLogLevel);
			}

			if (!syncSinks.empty())
			{
				_syncLogger = spdlog::logger(CreateUniqueLoggerName(false), syncSinks.begin(), syncSinks.end());
				_syncLogger->set_level(ToSpdLog(minSyncLogLevel));
			}

			if (!asyncSinks.empty())
			{
				std::call_once(_threadPoolInitFlag, []()
					{
						spdlog::init_thread_pool(8192, 4);
					});

				auto logger = std::make_shared<spdlog::async_logger>(
					CreateUniqueLoggerName(true),
					asyncSinks.begin(), asyncSinks.end(),
					spdlog::thread_pool(),
					spdlog::async_overflow_policy::block);
				spdlog::register_logger(logger);

				_asyncLogger = std::move(logger);
				_asyncLogger->set_level(ToSpdLog(minAsyncLogLevel));
				_asyncLogger->flush_on(spdlog::level::info);
			}

			assert(_syncLogger || _asyncLogger);
		}

		void Log(LogLevel level, const std::string& message, const std::source_location& location)
		{
			if (_syncLogger.has_value())
			{
				_syncLogger->log(ToSpdLog(location), ToSpdLog(level), message);
			}

			if (_asyncLogger)
			{
				_asyncLogger->log(ToSpdLog(location), ToSpdLog(level), message);
			}
		}

	private:
		auto ToSpdLog(LogLevel level) -> spdlog::level::level_enum
		{
			switch (level)
			{
			case LogLevel::Trace: return spdlog::level::level_enum::trace;
			case LogLevel::Debug: return spdlog::level::level_enum::debug;
			case LogLevel::Info: return spdlog::level::level_enum::info;
			case LogLevel::Warn: return spdlog::level::level_enum::warn;
			case LogLevel::Err: return spdlog::level::level_enum::err;
			case LogLevel::Critical: return spdlog::level::level_enum::critical;
			default:
				assert(false);
				return spdlog::level::level_enum::debug;
			}
		}

		auto ToSpdLog(const std::source_location& location) -> spdlog::source_loc
		{
			return spdlog::source_loc{
				location.file_name(),
				static_cast<int>(location.line()),
				location.function_name()
			};
		}

		auto CreateUniqueLoggerName(bool async) -> std::string
		{
			return std::format("{}_{}_logger", 
				async ? "async" : "sync", reinterpret_cast<size_t>(this));
		}

	private:
		std::optional<spdlog::logger> _syncLogger = std::nullopt;
		std::shared_ptr<spdlog::async_logger> _asyncLogger;

		static std::once_flag _threadPoolInitFlag;
	};

	std::once_flag SpdLogService::Impl::_threadPoolInitFlag;

	SpdLogService::SpdLogService(const SpdLogServiceConstructParam& param)
		: _impl(std::make_shared<Impl>(param))
	{
	}

	SpdLogService::~SpdLogService()
	{
	}

	void SpdLogService::Log(LogLevel level, const std::string& message, const std::source_location& location)
	{
		_impl->Log(level, message, location);
	}
}

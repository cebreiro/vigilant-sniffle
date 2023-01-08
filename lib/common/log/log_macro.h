#pragma once
#include "lib/common/log/log_service.h"

#ifndef __UNDEF_ALL_LOG

#define LOGT(logger, content) (logger).Log(cebreiro::LogLevel::Trace, (content));
#define LOG_GT(content) LOGT(*cebreiro::log::Global(), content)

#define LOGD(logger, content) (logger).Log(cebreiro::LogLevel::Debug, (content));
#define LOG_GD(content) LOGD(*cebreiro::log::Global(), content)

#define LOGI(logger, content) (logger).Log(cebreiro::LogLevel::Info, (content));
#define LOG_GI(content) LOGI(*cebreiro::log::Global(), content)

#define LOGW(logger, content) (logger).Log(cebreiro::LogLevel::Warn, (content));
#define LOG_GW(content) LOGW(*cebreiro::log::Global(), content)

#define LOGE(logger, content) (logger).Log(cebreiro::LogLevel::Err, (content));
#define LOG_GE(content) LOGE(*cebreiro::log::Global(), content)

#define LOGC(logger, content) (logger).Log(cebreiro::LogLevel::Critical, (content));
#define LOG_GC(content) LOGC(*cebreiro::log::Global(), content)

#else

#define LOGT(...)
#define LOG_GT(...)

#define LOGD(...)
#define LOG_GD(...)

#define LOGI(...)
#define LOG_GI(...)

#define LOGW(...)
#define LOG_GW(...)

#define LOGE(...)
#define LOG_GE(...)

#define LOGC(...)
#define LOG_GC(...)

#endif // !__UNDEF_ALL_LOG

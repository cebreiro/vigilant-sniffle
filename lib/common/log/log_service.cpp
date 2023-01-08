#include "log_service.h"

#include <atomic>

namespace cebreiro
{
	namespace log
	{
		namespace detail
		{
			static std::atomic<ILogService*> globalInstance = nullptr;
		}


		void SetGlobal(ILogService* service)
		{
			detail::globalInstance.store(service);
		}

		auto Global() -> ILogService*
		{
			return detail::globalInstance.load();
		}
	}
}
#include "service_locator.h"

#include "lib/common/stacktrace_exception.h"

namespace cebreiro
{
	auto ServiceLocator::LogService() const -> ILogService&
	{
		return *_logService;
	}

	auto ServiceLocator::GameDataSource() const -> gamedata::GameDataSource&
	{
		return *_gameDataSource;
	}

	auto ServiceLocator::LoginService() const -> ILoginService&
	{
		return *_loginService;
	}

	auto ServiceLocator::WorldService(int8_t worldId) const -> IWorldService&
	{
		return *FindWorldService(worldId);
	}

	auto ServiceLocator::WorldServices() const -> const std::vector<IWorldService*>&
	{
		return _worldServices;
	}

	auto ServiceLocator::FindWorldService(int8_t worldId) const -> IWorldService*
	{
		auto iter = _worldServiceIdIndexer.find(worldId);
		return iter != _worldServiceIdIndexer.end() ? iter->second : nullptr;
	}

	void ServiceLocator::SetLogService(ILogService* service)
	{
		_logService = service;
	}

	void ServiceLocator::SetGameDataSource(gamedata::GameDataSource* source)
	{
		_gameDataSource = source;
	}

	void ServiceLocator::SetLoginService(ILoginService* service)
	{
		_loginService = service;
	}

	void ServiceLocator::SetWorldService(int8_t worldId, IWorldService* service)
	{
		bool result = _worldServiceIdIndexer.try_emplace(worldId, service).second;
		if (!result)
		{
			throw StacktraceException(std::format("duplicated world id error. worldId: {}", worldId));
		}

		_worldServices.push_back(service);
	}
}

#include "network_executor.h"

#include <future>

namespace cebreiro::network
{
	NetworkExecutor::NetworkExecutor(size_t concurrency)
		: _workGuard(_asio::make_work_guard(_ioContext))
	{
		if (concurrency == 0)
		{
			concurrency = std::thread::hardware_concurrency();
		}

		std::vector<std::promise<std::thread::id>> promises;
		std::vector<std::future<std::thread::id>> futures;

		promises.resize(concurrency);
		futures.reserve(concurrency);

		_workers.resize(concurrency);

		for (size_t i = 0; i < concurrency; ++i)
		{
			std::promise<std::thread::id>& promise = promises[i];
			futures.push_back(promise.get_future());

			_workers[i] = std::thread([this, i, &promise]()
				{
					promise.set_value(std::this_thread::get_id());

			_ioContext.run();
				});
		}

		for (std::future<std::thread::id>& future : futures)
		{
			_workerIds.push_back(future.get());
		}
	}

	NetworkExecutor::NetworkExecutor()
		: NetworkExecutor(std::thread::hardware_concurrency())
	{
	}

	NetworkExecutor::~NetworkExecutor()
	{
		Stop();
	}

	void NetworkExecutor::Stop()
	{
		_ioContext.stop();

		for (std::thread& worker : _workers)
		{
			worker.join();
		}

		_workers.clear();
	}

	bool NetworkExecutor::IsRunningContext() const
	{
		return std::ranges::any_of(_workerIds, [current = std::this_thread::get_id()](const std::thread::id& workerId)
			{
				return workerId == current;
			});
	}

	void NetworkExecutor::Post(const std::function<void()>& function)
	{
		boost::asio::post(_ioContext, function);
	}

	auto NetworkExecutor::GetIoContext() -> _asio::io_context&
	{
		return _ioContext;
	}
}

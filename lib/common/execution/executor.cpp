#include "executor.h"

#include <cassert>
#include <unordered_map>
#include <shared_mutex>

#include "lib/common/execution/thread_pool.h"

namespace cebreiro
{
	Executor::~Executor()
	{
	}

	namespace detail
	{
		using executor_storage_t = std::unordered_map<std::thread::id, Executor*>;

		auto GetExecutorStorage() -> std::pair<std::shared_mutex, executor_storage_t>&
		{
			static std::pair<std::shared_mutex, executor_storage_t> instance;
			return instance;
		}
	}

	auto Executor::Current() -> Executor&
	{
		auto& [mutex, storage] = detail::GetExecutorStorage();

		std::thread::id current = std::this_thread::get_id();
		{
			std::shared_lock lock(mutex);

			auto iter = storage.find(current);
			if (iter != storage.end())
			{
				return *iter->second;
			}
		}

		return Executor::GetThreadPool();
	}

	auto Executor::GetThreadPool() -> Executor&
	{
		return ThreadPool::GetInstance();
	}

	void Executor::SetCurrent(Executor* executor)
	{
		assert(executor);

		auto& [mutex, storage] = detail::GetExecutorStorage();
		std::thread::id current = std::this_thread::get_id();
		{
			std::unique_lock lock(mutex);

			storage[current] = executor;
		}
	}

	void Executor::RemoveCurrent()
	{
		auto& [mutex, storage] = detail::GetExecutorStorage();
		std::thread::id current = std::this_thread::get_id();
		{
			std::unique_lock lock(mutex);

			storage.erase(current);
		}
	}
}

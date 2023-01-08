#include "thread_pool.h"

#include <vector>
#include <thread>
#include <future>
#include <boost/asio.hpp>
#include "lib/common/execution/executor.h"

namespace cebreiro
{
	class ThreadPool::Impl : public Executor
	{
	public:
		Impl(size_t count)
			: _workGuard(boost::asio::make_work_guard(_ioContext))
		{
			std::vector<std::promise<std::thread::id>> promises;
			std::vector<std::future<std::thread::id>> futures;

			size_t concurrency = count != 0 ? count : std::thread::hardware_concurrency();

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

						Executor::SetCurrent(this);
						_ioContext.run();

						Executor::RemoveCurrent();
					});
			}

			for (std::future<std::thread::id>& future : futures)
			{
				_workerIds.push_back(future.get());
			}
		}

		~Impl()
		{
			Stop();
		}

		bool IsRunningContext() const override
		{
			return std::ranges::any_of(_workerIds, [current = std::this_thread::get_id()](const std::thread::id& workerId)
				{
					return workerId == current;
				});
		}

		void Post(const std::function<void()>& function) override
		{
			boost::asio::post(_ioContext, function);
		}

		void Stop()
		{
			_ioContext.stop();

			for (std::thread& worker : _workers)
			{
				worker.join();
			}

			_workers.clear();
			_workerIds.clear();
		}

		auto GetIoContext() -> boost::asio::io_context&
		{
			return _ioContext;
		}

		auto GetConcurrency() -> size_t
		{
			return _workerIds.size();
		}

	private:
		boost::asio::io_context _ioContext;
		boost::asio::executor_work_guard<boost::asio::io_context::executor_type> _workGuard;

		std::vector<std::thread> _workers;
		std::vector<std::thread::id> _workerIds;
	};

	class ThreadPool::Strand::Impl : public Executor
	{
	public:
		explicit Impl(std::shared_ptr<ThreadPool::Impl> pool)
			: _pool(std::move(pool))
			, _strand(boost::asio::make_strand(_pool->GetIoContext()))
		{
		}

		bool IsRunningContext() const override
		{
			return _pool->IsRunningContext();
		}

		void Post(const std::function<void()>& function) override
		{
			boost::asio::post(_strand, function);
		}

	private:
		std::shared_ptr<ThreadPool::Impl> _pool;
		boost::asio::strand<boost::asio::any_io_executor> _strand;
	};

	ThreadPool::Strand::Strand(std::shared_ptr<Impl> impl)
		: _impl(std::move(impl))
	{
		assert(_impl);
	}

	bool ThreadPool::Strand::IsValid() const
	{
		return _impl.operator bool();
	}

	ThreadPool::Strand::operator Executor&()
	{
		return *_impl;
	}

	bool ThreadPool::Strand::IsRunningContext() const
	{
		return _impl->IsRunningContext();
	}

	void ThreadPool::Strand::Post(const std::function<void()>& function)
	{
		_impl->Post(function);
	}

	auto ThreadPool::GetInstance() -> ThreadPool&
	{
		static ThreadPool instance;
		return instance;
	}

	ThreadPool::ThreadPool(size_t poolSize)
		: _impl(std::make_shared<Impl>(poolSize))
	{
	}

	ThreadPool::ThreadPool()
		: ThreadPool(0)
	{
	}

	ThreadPool::~ThreadPool()
	{
	}

	ThreadPool::operator Executor&()
	{
		return *_impl;
	}

	bool ThreadPool::IsRunningContext() const
	{
		return _impl->IsRunningContext();
	}

	void ThreadPool::Post(const std::function<void()>& function)
	{
		_impl->Post(function);
	}

	void ThreadPool::Stop()
	{
		_impl->Stop();
	}

	auto ThreadPool::MakeStrand() -> Strand
	{
		return Strand(std::make_shared<Strand::Impl>(_impl));
	}

	auto ThreadPool::GetConcurrency() -> size_t
	{
		return _impl->GetConcurrency();
	}
}

#pragma once
#include <vector>
#include <thread>
#include <boost/asio.hpp>
#include "lib/network/type_alias.h"
#include "lib/common/execution/executor.h"

namespace cebreiro::network
{
	class NetworkExecutor : public Executor
	{
	public:
		explicit NetworkExecutor(size_t concurrency);
		NetworkExecutor();
		~NetworkExecutor() override;

		void Stop();

		bool IsRunningContext() const override;
		void Post(const std::function<void()>& function) override;

		auto GetIoContext() -> _asio::io_context&;

	private:
		_asio::io_context _ioContext;
		_asio::executor_work_guard<_asio::io_context::executor_type> _workGuard;

		std::vector<std::thread> _workers;
		std::vector<std::thread::id> _workerIds;
	};
}
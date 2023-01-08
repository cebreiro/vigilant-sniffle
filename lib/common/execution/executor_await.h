#pragma once
#include <coroutine>
#include "lib/common/execution/executor.h"

namespace cebreiro
{
	struct ExecutorAwait
	{
		bool await_ready() const;
		void await_suspend(std::coroutine_handle<> handle);
		void await_resume();

		std::atomic<bool> posted = false;
		std::shared_ptr<Executor> executor;
	};

	auto operator co_await(Executor& executor) -> ExecutorAwait;
}
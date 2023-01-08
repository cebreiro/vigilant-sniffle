#include "executor_await.h"

namespace cebreiro
{
	bool ExecutorAwait::await_ready() const
	{
		return posted.load();
	}

	void ExecutorAwait::await_suspend(std::coroutine_handle<> handle)
	{
		executor->Post([this, handle]()
			{
				posted = true;
				handle.resume();
			});
	}

	void ExecutorAwait::await_resume()
	{
	}

	auto operator co_await(Executor& executor) -> ExecutorAwait
	{
		return ExecutorAwait{
			.posted = false,
			.executor = executor.shared_from_this()
		};
	}
}

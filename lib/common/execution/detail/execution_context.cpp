#include "execution_context.h"

namespace cebreiro
{
	ExecutionContext<void>::ExecutionContext(std::shared_ptr<detail::ExecutionContextImpl<void>> impl)
		: _impl(std::move(impl))
	{
	}

	ExecutionContext<void>::~ExecutionContext()
	{
	}

	void ExecutionContext<void>::Cancel()
	{
		_impl->Cancel();
	}

	void ExecutionContext<void>::Set()
	{
		_impl->Set();
	}

	void ExecutionContext<void>::AddContinuation(const std::function<void()>& continuation)
	{
		_impl->AddContinuation(continuation);
	}

	void ExecutionContext<void>::SetException(const std::exception_ptr& exception)
	{
		_impl->SetException(exception);
	}

	void ExecutionContext<void>::Get()
	{
		return _impl->Get();
	}

	auto ExecutionContext<void>::Wait() -> FutureStatus
	{
		return _impl->Wait();
	}

	auto ExecutionContext<void>::WaitFor(std::chrono::milliseconds milliseconds) -> FutureStatus
	{
		return _impl->WaitFor(milliseconds);
	}

	bool ExecutionContext<void>::IsValid() const
	{
		return _impl.operator bool();
	}

	bool ExecutionContext<void>::IsPending() const
	{
		return _impl->IsPending();
	}

	bool ExecutionContext<void>::IsDone() const
	{
		return _impl->IsDone();
	}

	bool ExecutionContext<void>::IsCanceled() const
	{
		return _impl->IsCanceled();
	}

	auto ExecutionContext<void>::Status() -> FutureStatus
	{
		return _impl->Status();
	}

}
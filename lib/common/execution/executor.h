#pragma once
#include <memory>
#include <functional>

namespace cebreiro
{
	class Executor : public std::enable_shared_from_this<Executor>
	{
	public:
		virtual ~Executor();

		virtual bool IsRunningContext() const = 0;
		virtual void Post(const std::function<void()>& function) = 0;

		static auto Current() -> Executor&;
		static auto GetThreadPool() -> Executor&;

		static void SetCurrent(Executor* executor);
		static void RemoveCurrent();
	};
}
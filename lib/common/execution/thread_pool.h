#pragma once
#include <memory>
#include <functional>

namespace cebreiro
{
	class Executor;

	class ThreadPool
	{
		class Impl;

	public:
		class Strand
		{
		public:
			class Impl;

		public:
			explicit Strand(std::shared_ptr<Impl> impl);
			Strand() = default;

			bool IsValid() const;

			operator Executor&();

			bool IsRunningContext() const;
			void Post(const std::function<void()>& function);

		private:
			std::shared_ptr<Impl> _impl;
		};

	public:
		static auto GetInstance() -> ThreadPool&;

		explicit ThreadPool(size_t poolSize);
		ThreadPool();
		~ThreadPool();

		operator Executor&();

		bool IsRunningContext() const;
		void Post(const std::function<void()>& function);

		void Stop();

		auto MakeStrand() -> Strand;
		auto GetConcurrency() -> size_t;

	private:
		std::shared_ptr<Impl> _impl;
	};
}

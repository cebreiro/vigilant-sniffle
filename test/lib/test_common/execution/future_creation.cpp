#include <gtest/gtest.h>

#include "test_executor.h"
#include "lib/common/execution/future.h"
#include "lib/common/execution/promise.h"


constexpr int32_t futureCreationTestExpected = 111111111;
int32_t futureCreationTestFunction()
{
	return futureCreationTestExpected;
}

TEST(FutureCreation, CreateFromCallable)
{
	using namespace cebreiro;

	// arrange
	std::shared_ptr<TestExecutor> e = CreateExecutor();
	TestExecutor& executor = *e;

	struct BindTestClass1
	{
		auto Method() const -> int32_t
		{
			return value;
		}

		int32_t value = 0;
	};

	struct FunctionObjectClass
	{
		auto operator()() const -> int32_t
		{
			return value;
		}

		int32_t value = 0;
	};

	// act
	int32_t value = futureCreationTestExpected;
	Future<int32_t> f1 = Post([value]() { return value; }, executor);
	Future<int32_t> f2 = Post(futureCreationTestFunction, executor);

	BindTestClass1 btc1{ .value = futureCreationTestExpected };
	Future<int32_t> f3 = Post(std::bind(&BindTestClass1::Method, btc1), executor);

	FunctionObjectClass fo{ .value = futureCreationTestExpected };
	Future<int32_t> f4 = Post(fo, executor);

	// assert
	ASSERT_EQ(f1.Get(), futureCreationTestExpected);
	ASSERT_EQ(f2.Get(), futureCreationTestExpected);
	ASSERT_EQ(f3.Get(), futureCreationTestExpected);
	ASSERT_EQ(f4.Get(), futureCreationTestExpected);
}

TEST(FutureCreation, CreateFromPromise)
{
	using namespace cebreiro;

	// arrange
	std::shared_ptr<TestExecutor> e = CreateExecutor();
	TestExecutor& executor = *e;

	Promise<int32_t> promise;
	Future<int32_t> future = promise.GetFuture();

	// act
	executor.Post(detail::Wrap([promise = std::move(promise)]() mutable
		{
			promise.Set(futureCreationTestExpected);

		}));

	// assert
	ASSERT_EQ(future.Get(), futureCreationTestExpected);
}

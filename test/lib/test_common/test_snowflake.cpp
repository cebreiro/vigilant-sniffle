#include "gtest/gtest.h"

#include "lib/common/snowflake.h"

TEST(Snowflake, Generate_4095_Uids_Per_Seconds)
{
	// 2021-01-01 00:00:00
	constexpr uint64_t epoch = 1609426800000i64;
	constexpr uint64_t maxSequenceMask = cebreiro::snowflake::MAX_SEQUENCE_MASK;
	constexpr uint64_t sequenceOverflowCount = maxSequenceMask + 1;

	class StubClock
	{
	public:
		static auto Now() -> uint64_t
		{
			static uint64_t count = 0;

			if (++count >= sequenceOverflowCount)
			{
				return epoch + 1;
			}

			return epoch;
		}
	};

	using Snowflake = cebreiro::basic_snowflake<cebreiro::snowflake::ThreadUnsafe, StubClock, epoch>;

	Snowflake snowflake(0, 0);

	uint64_t first = 0;
	uint64_t prev = 0;

	for (uint64_t i = 1; i <= sequenceOverflowCount; ++i)
	{
		uint64_t current = snowflake.Generate();

		if (i == 1)
		{
			first = current;
		}
		else if (i == sequenceOverflowCount)
		{
			ASSERT_EQ(0, first & maxSequenceMask);
			ASSERT_EQ(0, current & maxSequenceMask);
		}
		else
		{
			ASSERT_EQ(prev + 1, current);
		}

		prev = current;
	}
}
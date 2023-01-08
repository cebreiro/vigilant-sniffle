#include "gtest/gtest.h"

#include "lib/network/receive_buffer.h"

TEST(ReceiveBuffer, DefaultConstruction)
{
	using namespace cebreiro::network;

	// arrange
	ReceiveBuffer buffer;

	// act
	const char* data = buffer.Data();
	size_t size = buffer.Size();
	size_t usedSize = buffer.ReceiveSize();

	// assert
	ASSERT_EQ(data, nullptr);
	ASSERT_EQ(size, 0);
	ASSERT_EQ(usedSize, 0);
}

TEST(ReceiveBuffer, Construction)
{
	using namespace cebreiro::network;

	// arrange
	constexpr size_t BUFFER_SIZE = 1024;
	ReceiveBuffer buffer(BUFFER_SIZE);

	// act
	const char* data = buffer.Data();
	size_t size = buffer.Size();
	size_t usedSize = buffer.ReceiveSize();

	// assert
	ASSERT_NE(data, nullptr);
	ASSERT_EQ(size, BUFFER_SIZE);
	ASSERT_EQ(usedSize, 0);
}

TEST(ReceiveBuffer, AddUsedSize)
{
	using namespace cebreiro::network;

	// arrange
	constexpr size_t BUFFER_SIZE = 1024;
	ReceiveBuffer buffer(BUFFER_SIZE);

	// act
	constexpr size_t USED_SIZE = 128;
	buffer.AddReceiveSize(USED_SIZE);

	const char* data = buffer.Data();
	size_t size = buffer.Size();
	size_t usedSize = buffer.ReceiveSize();

	// assert
	ASSERT_NE(data, nullptr);
	ASSERT_EQ(size, BUFFER_SIZE);
	ASSERT_EQ(usedSize, USED_SIZE);
}

TEST(ReceiveBuffer, SliceFront)
{
	using namespace cebreiro::network;

	// arrange
	constexpr size_t BUFFER_SIZE = 8;
	ReceiveBuffer buffer(BUFFER_SIZE);

	constexpr size_t TEST_DATA_SIZE = 6;
	char testData[TEST_DATA_SIZE] = { 'a', 'b', 'c', 'd', 'e', 'f'};

	// act
	std::copy_n(testData, TEST_DATA_SIZE, buffer.Data());
	buffer.AddReceiveSize(TEST_DATA_SIZE);

	constexpr size_t SLICE_SIZE = 2;
	Buffer slice1 = buffer.SliceFront(SLICE_SIZE);
	size_t slice1Size = slice1.Size();

	Buffer slice2 = buffer.SliceFront(SLICE_SIZE);
	size_t slice2Size = slice2.Size();

	size_t size = buffer.Size();
	size_t usedSize = buffer.ReceiveSize();

	// assert
	ASSERT_EQ(slice1Size, SLICE_SIZE);
	ASSERT_EQ(slice2Size, SLICE_SIZE);

	ASSERT_EQ(size, BUFFER_SIZE - SLICE_SIZE - SLICE_SIZE);
	ASSERT_EQ(usedSize, TEST_DATA_SIZE - SLICE_SIZE - SLICE_SIZE);

	ASSERT_EQ('a', *slice1.Data());
	ASSERT_EQ('b', *(slice1.Data() + 1));

	ASSERT_EQ('c', *slice2.Data());
	ASSERT_EQ('d', *(slice2.Data() + 1));
	
	ASSERT_EQ('e', *buffer.Data());
	ASSERT_EQ('f', *(buffer.Data() + 1));
}

TEST(ReceiveBuffer, SliceFrontAll)
{
	using namespace cebreiro::network;

	// arrange
	constexpr size_t BUFFER_SIZE = 6;
	ReceiveBuffer buffer(BUFFER_SIZE);

	char testData[BUFFER_SIZE] = { 'a', 'b', 'c', 'd', 'e', 'f'};

	// act
	std::copy_n(testData, BUFFER_SIZE, buffer.Data());
	buffer.AddReceiveSize(BUFFER_SIZE);

	Buffer slice1 = buffer.SliceFront(BUFFER_SIZE);
	size_t slice1Size = slice1.Size();

	size_t size = buffer.Size();
	size_t usedSize = buffer.ReceiveSize();

	// assert
	ASSERT_EQ(slice1Size, BUFFER_SIZE);

	ASSERT_EQ(size, 0);
	ASSERT_EQ(usedSize, 0);

	ASSERT_EQ('a', *slice1.Data());
	ASSERT_EQ('b', *(slice1.Data() + 1));
	ASSERT_EQ('c', *(slice1.Data() + 2));
	ASSERT_EQ('d', *(slice1.Data() + 3));
	ASSERT_EQ('e', *(slice1.Data() + 4));
	ASSERT_EQ('f', *(slice1.Data() + 5));
	ASSERT_FALSE(buffer.IsValid());
}

TEST(ReceiveBuffer, SliceFrontOverCount)
{
	using namespace cebreiro::network;

	// arrange
	constexpr size_t BUFFER_SIZE = 8;
	ReceiveBuffer buffer(BUFFER_SIZE);

	// act
	buffer.AddReceiveSize(1);

	// assert
	ASSERT_ANY_THROW(buffer.SliceFront(buffer.ReceiveSize() + 1));
}

TEST(ReceiveBuffer, Resize)
{
	using namespace cebreiro::network;

	// arrange
	constexpr size_t BUFFER_SIZE = 8;
	ReceiveBuffer buffer(BUFFER_SIZE);

	constexpr size_t TEST_DATA_SIZE = 6;
	char testData[TEST_DATA_SIZE] = { 'a', 'b', 'c', 'd', 'e', 'f' };

	// act
	std::copy_n(testData, TEST_DATA_SIZE, buffer.Data());
	buffer.AddReceiveSize(TEST_DATA_SIZE);

	constexpr size_t BUFFER_RESIZE = BUFFER_SIZE * 2;
	buffer.Resize(BUFFER_RESIZE);

	size_t size = buffer.Size();
	size_t usedSize = buffer.ReceiveSize();

	// assert
	ASSERT_EQ(size, BUFFER_RESIZE);
	ASSERT_EQ(usedSize, TEST_DATA_SIZE);

	ASSERT_EQ('a', *buffer.Data());
	ASSERT_EQ('b', *(buffer.Data() + 1));
	ASSERT_EQ('c', *(buffer.Data() + 2));
	ASSERT_EQ('d', *(buffer.Data() + 3));
	ASSERT_EQ('e', *(buffer.Data() + 4));
	ASSERT_EQ('f', *(buffer.Data() + 5));
}

TEST(ReceiveBuffer, Reset)
{
	using namespace cebreiro::network;

	// arrange
	constexpr size_t BUFFER_SIZE = 6;
	ReceiveBuffer buffer(BUFFER_SIZE);

	// act
	buffer.Reset();

	size_t size = buffer.Size();
	size_t usedSize = buffer.ReceiveSize();

	// assert
	ASSERT_EQ(size, BUFFER_SIZE);
	ASSERT_EQ(usedSize, 0);
}
#include "gtest/gtest.h"

#include "lib/common/stream/stream_writer.h"

using cebreiro::StreamWriter;

#ifdef WIN32

constexpr int8_t required1 = 30;
constexpr int16_t required2 = 300;
constexpr int32_t required3 = 30000;
constexpr int64_t required4 = 300000000;

#pragma pack(push,1)

struct Data
{
	int8_t v1 = required1;
	int16_t v2 = required2;
	int32_t v3 = required3;
	int64_t v4 = required4;
};

#pragma pack(pop)

TEST(StreamWriter, Writer_Integral)
{
	Data data1;
	char buffer[sizeof(data1)] = {};
	Data& data2 = *reinterpret_cast<Data*>(buffer);
	StreamWriter writer(buffer, sizeof(buffer));

	ASSERT_TRUE(writer.CanWrite(sizeof(required1)));
	ASSERT_NO_THROW(writer.WriteInt8(required1));

	ASSERT_TRUE(writer.CanWrite(sizeof(required2)));
	ASSERT_NO_THROW(writer.WriteInt16(required2));

	ASSERT_TRUE(writer.CanWrite(sizeof(required3)));
	ASSERT_NO_THROW(writer.WriteInt32(required3));

	ASSERT_TRUE(writer.CanWrite(sizeof(required4)));
	ASSERT_NO_THROW(writer.WriteInt64(required4));

	ASSERT_FALSE(writer.CanWrite(1));
	ASSERT_ANY_THROW(writer.WriteInt8(1));

	ASSERT_EQ(data1.v1, data2.v1);
	ASSERT_EQ(data1.v2, data2.v2);
	ASSERT_EQ(data1.v3, data2.v3);
	ASSERT_EQ(data1.v4, data2.v4);
}

TEST(StreamWriter, Write_Buffer)
{
	Data data1;
	char buffer[sizeof(data1)] = {};
	Data& data2 = *reinterpret_cast<Data*>(buffer);
	StreamWriter writer(buffer, sizeof(buffer));

	ASSERT_TRUE(writer.CanWrite(sizeof(data1)));
	ASSERT_NO_THROW(writer.WriteBytes(reinterpret_cast<const char*>(&data1), sizeof(data1)));

	ASSERT_FALSE(writer.CanWrite(1));
	ASSERT_ANY_THROW(writer.WriteInt8(1));

	ASSERT_EQ(data1.v1, data2.v1);
	ASSERT_EQ(data1.v2, data2.v2);
	ASSERT_EQ(data1.v3, data2.v3);
	ASSERT_EQ(data1.v4, data2.v4);
}

TEST(StreamWriter, Write_ZeroBytes)
{
	Data data1;
	char buffer[sizeof(data1)] = {};
	Data& data2 = *reinterpret_cast<Data*>(buffer);
	StreamWriter writer(buffer, sizeof(buffer));

	constexpr size_t zeroBytesLength = sizeof(required1) + sizeof(required2) + sizeof(required3);

	ASSERT_TRUE(writer.CanWrite(zeroBytesLength));
	ASSERT_NO_THROW(writer.WriteZeroBytes(zeroBytesLength));

	ASSERT_TRUE(writer.CanWrite(sizeof(required4)));
	ASSERT_NO_THROW(writer.WriteInt64(required4));

	ASSERT_FALSE(writer.CanWrite(1));
	ASSERT_ANY_THROW(writer.WriteInt8(1));

	ASSERT_EQ(0, data2.v1);
	ASSERT_EQ(0, data2.v2);
	ASSERT_EQ(0, data2.v3);
	ASSERT_EQ(data1.v4, data2.v4);
}

TEST(StreamWriter, SetOffset)
{
	Data data1;
	char buffer[sizeof(data1)] = {};
	Data& data2 = *reinterpret_cast<Data*>(buffer);
	StreamWriter writer(buffer, sizeof(buffer));

	constexpr size_t offset = sizeof(required1) + sizeof(required2) + sizeof(required3);
	writer.SetOffset(offset);

	ASSERT_TRUE(writer.CanWrite(sizeof(required4)));
	ASSERT_NO_THROW(writer.WriteInt64(required4));

	ASSERT_FALSE(writer.CanWrite(1));
	ASSERT_ANY_THROW(writer.WriteInt8(1));

	ASSERT_EQ(0, data2.v1);
	ASSERT_EQ(0, data2.v2);
	ASSERT_EQ(0, data2.v3);
	ASSERT_EQ(data1.v4, data2.v4);
}

#endif
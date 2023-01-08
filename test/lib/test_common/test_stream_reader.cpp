#include "gtest/gtest.h"

#include "lib/common/stream/stream_reader.h"

using cebreiro::StreamReader;

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

TEST(StreamReader, Read_Integral)
{
	Data data;
	StreamReader reader(reinterpret_cast<char*>(&data), sizeof(data));

	ASSERT_TRUE(reader.CanRead(sizeof(required1)));
	ASSERT_EQ(reader.ReadInt8(), required1);

	ASSERT_TRUE(reader.CanRead(sizeof(required2)));
	ASSERT_EQ(reader.ReadInt16(), required2);

	ASSERT_TRUE(reader.CanRead(sizeof(required3)));
	ASSERT_EQ(reader.ReadInt32(), required3);

	ASSERT_TRUE(reader.CanRead(sizeof(required4)));
	ASSERT_EQ(reader.ReadInt64(), required4);

	ASSERT_FALSE(reader.CanRead(1));
	ASSERT_ANY_THROW(reader.ReadInt8());
}

TEST(StreamReader, Read_Buffer)
{
	Data data1;
	StreamReader reader(reinterpret_cast<char*>(&data1), sizeof(data1));

	char buffer[sizeof(data1)] = {};
	reader.Read(buffer, sizeof(buffer));

	Data& data2 = *reinterpret_cast<Data*>(buffer);

	ASSERT_FALSE(reader.CanRead(1));

	ASSERT_EQ(data1.v1, data2.v1);
	ASSERT_EQ(data1.v2, data2.v2);
	ASSERT_EQ(data1.v3, data2.v3);
	ASSERT_EQ(data1.v4, data2.v4);
}

TEST(StreamReader, Skip)
{
	Data data;
	StreamReader reader(reinterpret_cast<char*>(&data), sizeof(data));

	ASSERT_NO_THROW(reader.Skip(sizeof(required1)));
	ASSERT_NO_THROW(reader.Skip(sizeof(required2)));
	ASSERT_NO_THROW(reader.Skip(sizeof(required3)));

	ASSERT_TRUE(reader.CanRead(sizeof(required4)));
	ASSERT_EQ(reader.ReadInt64(), required4);

	ASSERT_FALSE(reader.CanRead(1));
	ASSERT_ANY_THROW(reader.Skip(1));
}

TEST(StreamReader, SetOffset)
{
	Data data;
	StreamReader reader(reinterpret_cast<char*>(&data), sizeof(data));

	ASSERT_NO_THROW(reader.SetOffset(sizeof(required1) + sizeof(required2) + sizeof(required3)));
	ASSERT_TRUE(reader.CanRead(sizeof(required4)));
	ASSERT_EQ(reader.ReadInt64(), required4);

	ASSERT_NO_THROW(reader.SetOffset(sizeof(required1) + sizeof(required2) + sizeof(required3) + sizeof(required4)));
	ASSERT_FALSE(reader.CanRead(1));
}

#endif
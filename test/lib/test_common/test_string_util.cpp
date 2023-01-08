#include "gtest/gtest.h"

#include "lib/common/string_util.h"

TEST(ConvertUtil, UTF16_TO_MB)
{
	const wchar_t* u16 = L"a가b나c다";
	const char* mb = "a가b나c다";

	std::wstring origin(u16);
	std::string converted = cebreiro::ToMBString(origin);

	ASSERT_EQ(converted, std::string(mb));
}

TEST(ConvertUtil, MB_TO_UTF16)
{
	const wchar_t* u16 = L"a가b나c다";
	const char* mb = "a가b나c다";

	std::string origin(mb);
	std::wstring converted = cebreiro::ToUTF16(origin);

	ASSERT_EQ(converted, std::wstring(u16));
}
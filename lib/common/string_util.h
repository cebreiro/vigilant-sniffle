#pragma once
#include <string>

namespace cebreiro
{
	auto ToMBString(const std::wstring& u16) -> std::string;
	auto ToUTF16(const std::string& mb) -> std::wstring;
}
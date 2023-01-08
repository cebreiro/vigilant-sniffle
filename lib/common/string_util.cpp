#include "string_util.h"

#include <cassert>
#include <locale>

namespace cebreiro
{
	auto ToMBString(const std::wstring& u16) -> std::string
	{
		using codecvt_t = std::codecvt<wchar_t, char, std::mbstate_t>;
		const codecvt_t& codecvt = std::use_facet<codecvt_t>(std::locale());

		std::string string((u16.size() + 1) * codecvt.max_length(), '\0');
		[[maybe_unused]] size_t size = string.size();
		[[maybe_unused]] size_t capacity = string.capacity();

		const wchar_t* from_next = nullptr;
		char* to_next = nullptr;

		std::mbstate_t state = {};
		(void)codecvt.out(
			state,
			u16.data(),
			u16.data() + u16.size(),
			from_next,
			string.data(),
			string.data() + string.capacity(),
			to_next
		);

		std::erase_if(string, [](char ch)
		{
			return ch == '\0';
		});

		return string;
	}

	auto ToUTF16(const std::string& mb) -> std::wstring
	{
		using codecvt_t = std::codecvt<wchar_t, char, std::mbstate_t>;
		const codecvt_t& codecvt = std::use_facet<codecvt_t>(std::locale());

		std::wstring wstring((mb.size() + 1) * codecvt.max_length(), L'\0');

		const char* from_next = nullptr;
		wchar_t* to_next = nullptr;

		std::mbstate_t state = {};
		(void)codecvt.in(
			state,
			mb.data(),
			mb.data() + mb.size(),
			from_next,
			wstring.data(),
			wstring.data() + wstring.size(),
			to_next
		);

		std::erase_if(wstring, [](wchar_t ch)
		{
			return ch == L'\0';
		});

		return wstring;
	}
}

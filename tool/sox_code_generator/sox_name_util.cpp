#include "sox_name_util.h"

#include <cassert>

#include "lib/common/log/log_macro.h"

namespace sr = std::ranges;

namespace cebreiro
{
	std::vector<char> SoxHungarianSingleLiteral = { 'n', 'f', 'b', 's' };


	auto ParseFileName(const std::string& fileName) -> SoxNameNotation
	{
		if (sr::all_of(fileName, [](char ch) { return std::isupper(ch) || std::isdigit(ch) || ch == '_'; }))
		{
			return SoxNameNotation::AllUpperUnderbar;
		}
		else if (sr::all_of(fileName, [](char ch) { return std::islower(ch) || std::isdigit(ch) || ch == '_'; }))
		{
			return SoxNameNotation::AllLowerUnderbar;
		}

		return SoxNameNotation::Pascal;
	}

	auto ToPascal(SoxNameNotation notation, const std::string& str) -> std::string
	{
		if (notation == SoxNameNotation::Pascal)
		{
			return str;
		}

		std::string result = str;

		if (notation == SoxNameNotation::AllUpperUnderbar)
		{
			sr::transform(result, result.begin(), [](char ch)
				{
					return static_cast<char>(std::tolower(ch));
				});
		}

		result[0] = static_cast<char>(std::toupper(result[0]));
		for (size_t i = 1; i < result.size(); ++i)
		{
			if (result[i - 1] == '_')
			{
				result[i] = static_cast<char>(std::toupper(result[i]));
			}
		}

		result.erase(sr::remove_if(result, [](char ch)
			{
				return ch == '_';
			}).begin(), result.end());

		return result;
	}

	auto ToFileNameConvention(SoxNameNotation notation, const std::string& str) -> std::string
	{
		if (notation == SoxNameNotation::Pascal)
		{
			std::string ret;

			for (size_t i = 0; i < str.length(); ++i)
			{
				char ch = str[i];
				if (std::isupper(ch))
				{
					if (i != 0)
					{
						ret += '_';
					}

					ret += static_cast<char>(std::tolower(ch));
				}
				else
				{
					ret += ch;
				}
			}

			return ret;
		}

		std::string ret;
		sr::transform(str, std::back_inserter(ret), [](char ch)
			{
				return static_cast<char>(std::tolower(ch));
			});

		return ret;
	}

	bool CheckHungarianTypeString(const std::string& str)
	{
		if (sr::any_of(SoxHungarianSingleLiteral, [&str](char ch) { return ch == str[0]; }))
		{
			if (std::isupper(str[1]))
			{
				return true;
			}
		}

		if (str.starts_with("sz") && std::isupper(str[2]))
		{
			return true;
		}

		return false;
	}

	auto ParseColumnName(const std::string& columnName) -> SoxNameNotation
	{
		if (sr::all_of(columnName, [](char ch) { return std::isupper(ch) || std::isdigit(ch) || ch == '_'; }))
		{
			return SoxNameNotation::AllUpperUnderbar;
		}
		else if (sr::all_of(columnName, [](char ch) { return std::islower(ch) || std::isdigit(ch) || ch == '_'; }))
		{
			return SoxNameNotation::AllLowerUnderbar;
		}
		else if (CheckHungarianTypeString(columnName))
		{
			return SoxNameNotation::Hungarian;
		}

		LOG_GW(std::format("sox column notation parse fail, column name: [{}]", columnName));

		return SoxNameNotation::ParsingFailed;
	}

	auto ToMemberConvention(SoxNameNotation notation, const std::string& str) -> std::string
	{
		// exceptional case handling
		if (!str.compare("_index"))
		{
			return "index";
		}
		else if (!str.compare("_szName"))
		{
			return "name";
		}

		std::string result = str;

		if (notation == SoxNameNotation::Hungarian)
		{
			if (str.starts_with("sz"))
			{
				result.erase(result.begin(), result.begin() + 2);
			}
			else if (sr::any_of(SoxHungarianSingleLiteral, [&str](char ch) { return ch == str[0]; }))
			{
				result.erase(result.begin());
			}
			else
			{
				assert(false);
			}
		}
		else if (notation == SoxNameNotation::AllUpperUnderbar)
		{
			sr::transform(result, result.begin(), [](char ch)
				{
					return static_cast<char>(std::tolower(ch));
				});
		}

		for (size_t i = 1; i < result.size(); ++i)
		{
			if (result[i - 1] == '_')
			{
				result[i] = static_cast<char>(std::toupper(result[i]));
			}
		}

		result.erase(sr::remove_if(result, [](char ch)
			{
				return ch == '_';
			}).begin(), result.end());

		result[0] = static_cast<char>(std::tolower(result[0]));

		if (std::isdigit(result[0]) || !result.compare("int") || !result.compare("default"))
		{
			result.insert(0, "_");
		}

		return result;
	}
}
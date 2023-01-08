#include "stacktrace_exception.h"

#include <sstream>
#include <regex>
#include <format>
#include <filesystem>
#include <boost/algorithm/string.hpp>
#include <boost/stacktrace.hpp>

namespace cebreiro
{
	std::string MakeStacktraceMessage(std::string_view exceptionMessage)
	{
		std::string stacktrace;
		{
			std::ostringstream temp;
			temp << boost::stacktrace::stacktrace();

			stacktrace = temp.str();
		}

		std::vector<std::string> lines;
		boost::split(lines, stacktrace, boost::is_any_of("\n"));

		std::ostringstream oss;
		oss << exceptionMessage;

		if (exceptionMessage.back() != '\n')
		{
			oss << '\n';
		}

		std::regex regex(".*[0-9]#(.*)at (.*)(:.*$)");
		std::smatch match;
		for (size_t i = 3; i < lines.size(); ++i)
		{
			if (std::regex_match(lines[i], match, regex) && match.size() >= 4)
			{
				std::string filename = std::filesystem::path(match[2].str()).filename().string();
				oss << std::format("    at{}({}{})\n", match[1].str(), filename, match[3].str());
			}
		}

		return oss.str();
	}

	StacktraceException::StacktraceException(std::string exceptionMessage)
		: _message(MakeStacktraceMessage(std::move(exceptionMessage)))
	{
	}

	const char* StacktraceException::what() const
	{
		return _message.c_str();
	}
}
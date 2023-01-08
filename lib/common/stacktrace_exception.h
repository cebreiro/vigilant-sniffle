#pragma once
#include <string>
#include <stdexcept>

namespace cebreiro
{
	class StacktraceException : public std::exception
	{
	public:
		explicit StacktraceException(std::string exceptionMessage);

		const char* what() const override;

	private:
		std::string _message;
	};
}
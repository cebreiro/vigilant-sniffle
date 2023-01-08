#include "text_writer.h"

namespace cebreiro
{
	void TextWriter::Write(const std::string& text)
	{
		_oss << text;
	}

	void TextWriter::WriteLine(const std::string& text)
	{
		_oss << std::format("{}\r\n", text);
	}

	void TextWriter::BreakLine()
	{
		_oss << "\r\n";
	}

	auto TextWriter::Get() const -> std::string
	{
		return _oss.str();
	}
}

#pragma once

namespace cebreiro
{
	class TextWriter
	{
	public:
		void Write(const std::string& text);
		void WriteLine(const std::string& text);

		template <typename... Args>
		void Write(const std::string& format, Args&&... args);

		template <typename... Args>
		void WriteLine(const std::string& format, Args&&... args);

		void BreakLine();

		auto Get() const -> std::string;

	private:
		std::ostringstream _oss;
	};

	template <typename ... Args>
	void TextWriter::Write(const std::string& format, Args&&... args)
	{
		Write(std::vformat(format, std::make_format_args(std::forward<Args>(args)...)));
	}

	template <typename ... Args>
	void TextWriter::WriteLine(const std::string& format, Args&&... args)
	{
		WriteLine(std::vformat(format, std::make_format_args(std::forward<Args>(args)...)));
	}
}

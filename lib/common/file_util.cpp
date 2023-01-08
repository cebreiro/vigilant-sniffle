#include "file_util.h"

#include <fstream>
#include <format>

#include "lib/common/stacktrace_exception.h"

namespace cebreiro
{
	auto ReadFile(const std::filesystem::path& filePath) -> std::vector<char>
	{
		std::ifstream ifs(filePath, std::ios::binary);
		if (!ifs.is_open())
		{
			throw StacktraceException(std::format("file open fail. {}", filePath.string()));
		}

		size_t fileSize = [](std::ifstream& ifs)
		{
			size_t current = ifs.tellg();

			ifs.seekg(0, std::ios::end);
			size_t fileSize = ifs.tellg();

			ifs.seekg(current, std::ios::beg);

			return fileSize;
			
		}(ifs);

		std::vector<char> buffer(fileSize);

		ifs.read(buffer.data(), static_cast<int64_t>(fileSize));
		ifs.close();

		return buffer;
	}
}

#include <format>
#include "lib/common/log/log_macro.h"
#include "lib/common/log/detail/spd_log_service.h"
#include "lib/common/stacktrace_exception.h"
#include "lib/game_base/data/sox/sox_file.h"
#include "sox_class_generator.h"

namespace fs = std::filesystem;
namespace sr = std::ranges;
namespace srv = sr::views;

void ReviseInvalidData(cebreiro::gamebase::SoxFile& soxFile)
{
	for (size_t i = 0; i < soxFile.columnNames.size(); ++i)
	{
		std::string& columnName = soxFile.columnNames[i].name;
		if (sr::any_of(columnName, [](char ch) { return ch == '*'; }))
		{
			std::string temp = columnName;
			sr::transform(columnName, columnName.begin(), [](char ch)
				{
					if (ch == '*')
					{
						return 'x';
					}

			return ch;
				});

			LOG_GW(std::format("invalid column: [{}] is revised to: [{}]", temp, columnName));
		}

		if (sr::any_of(columnName, [](char ch) { return std::isspace(ch); }))
		{
			std::string temp = columnName;
			sr::transform(columnName, columnName.begin(), [](char ch)
				{
					if (std::isspace(ch))
					{
						return '_';
					}

			return ch;
				});

			LOG_GW(std::format("invalid column: [{}] is revised to: [{}]", temp, columnName))
		}

		if (!columnName.compare("_ATTACK4RESERVED4"))
		{
			if (i < soxFile.columnNames.size() - 1)
			{
				std::string& next = soxFile.columnNames[i + 1].name;
				if (!next.compare("_ATTACK4RESERVED4"))
				{
					std::pair temp = { columnName , next };
					columnName = "_ATTACK4RESERVED2";
					next = "_ATTACK4RESERVED3";

					LOG_GW(std::format("invalid column [{}, {}] is revised to: [{}, {}]",
						temp.first, temp.second, columnName, next))
				}
			}
		}

		if (!columnName.compare("_ATTACK3RESERVED3"))
		{
			if (i < soxFile.columnNames.size() - 1)
			{
				std::string& next = soxFile.columnNames[i + 1].name;
				if (!next.compare("_ATTACK3RESERVED3"))
				{
					std::string temp = columnName;

					std::string& prev = soxFile.columnNames[i - 1].name;
					if (!prev.compare("_ATTACK3RESERVED1"))
					{
						columnName = "_ATTACK3RESERVED2";
					}
					else
					{
						columnName = "_ATTACK4RESERVED2";
					}

					LOG_GW(std::format("invalid column: [{}] is revised to: [{}]", temp, columnName))
				}
			}
		}
	}
}

int main(int argc, char* argv[])
{
	using namespace cebreiro;

	SpdLogServiceConstructParam param{
		.console = SpdLogServiceConstructParam::Console{
			.async = false,
			.level = LogLevel::Debug
		},
		.dailyFile = SpdLogServiceConstructParam::DailyFile{
			.path = "logs/log.txt",
			.level = LogLevel::Debug
		},
	};

	std::unique_ptr<ILogService> logService = std::make_unique<SpdLogService>(param);
	log::SetGlobal(logService.get());

	(void)argc;
	(void)argv;

	const char* input = "C:/Users/Beco/Documents/작업자료/SL/ShiningLoreOnlineII/Shining Lore Online/Data/Misc/";
	[[maybe_unused]] const char* output = "F:/test/";

	fs::path inputPath(input);

	auto view = fs::directory_iterator(inputPath)
		| srv::transform([](const fs::directory_entry& entry) { return entry.path(); })
		| srv::filter([](const fs::path& path)
			{
				if (!path.has_filename() || !path.has_extension())
				{
					return false;
				}

				const char* extension = ".sox";
				return ::_strnicmp(path.extension().string().c_str(), extension, ::strlen(extension)) == 0;
			})
		| srv::transform([](const fs::path& path)
		{
			gamebase::SoxFile soxFile(path);
			ReviseInvalidData(soxFile);

			return soxFile;
		})
		| srv::transform([](const gamebase::SoxFile& soxFile) -> std::tuple<std::string, std::string, std::string>
		{
			SoxClassGenerator generator(soxFile);

			return { generator.GetClassFileName(), generator.GenerateHeader(), generator.GenerateCXX() };
		});

	for (const auto& [fileName, header, cxx] : view)
	{
		std::filesystem::path directory(output);
		{
			std::filesystem::path filePath = directory / std::format("{}.h", fileName);
			std::ofstream ofs(filePath, std::ios::binary);
			if (!ofs.is_open())
			{
				throw StacktraceException(std::format("fail to open file. path: {}", filePath.string()));
			}

			ofs.write(header.data(), static_cast<int64_t>(header.size()));
		}
		{
			std::filesystem::path filePath = directory / std::format("{}.cpp", fileName);
			std::ofstream ofs(filePath, std::ios::binary);
			if (!ofs.is_open())
			{
				throw StacktraceException(std::format("fail to open file. path: {}", filePath.string()));
			}

			ofs.write(cxx.data(), static_cast<int64_t>(cxx.size()));
		}
	}

	return 0;
}
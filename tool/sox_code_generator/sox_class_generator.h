#pragma once
#include "sox_name_util.h"

namespace cebreiro
{
	namespace gamebase
	{
		struct SoxFile;
		struct SoxColumn;
	}

	class SoxClassGenerator
	{
	public:
		explicit SoxClassGenerator(const gamebase::SoxFile& soxFile);
		~SoxClassGenerator();

		auto GenerateHeader() const -> std::string;
		auto GenerateCXX() const -> std::string;

		auto GetClassFileName() const -> std::string;

	private:
		auto GetMemberName(const gamebase::SoxColumn& column) const -> std::string;

	private:
		const gamebase::SoxFile& _soxFile;

		SoxNameNotation _fileNotation;
		SoxNameNotation _columnNotation;
		std::string _className;
		std::string _containerName;
		int64_t _index = -1;
	};
}
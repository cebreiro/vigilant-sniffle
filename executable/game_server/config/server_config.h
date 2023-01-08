#pragma once
#include "nlohmann/json.hpp"

namespace cebreiro
{
	struct LogConfig
	{
		friend void from_json(const nlohmann::json& j, LogConfig& config);

		struct Console
		{
			friend void from_json(const nlohmann::json& j, Console& config);

			bool async = false;
			int32_t level = 1;
		};
		Console console;

		struct DailyFile
		{
			friend void from_json(const nlohmann::json& j, DailyFile& config);

			std::string path;
			int32_t level = 0;
		};
		DailyFile dailyFile;
	};

	struct ExecutorConfig
	{
		friend void from_json(const nlohmann::json& j, ExecutorConfig& config);

		int32_t networkConcurrency = 0;
		int32_t dbConcurrency = 0;
	};
	
	struct GameDataConfig
	{
		friend void from_json(const nlohmann::json& j, GameDataConfig& config);

		std::string path;
	};

	struct GameDBConfig
	{
		friend void from_json(const nlohmann::json& j, GameDBConfig& config);

		std::string odbcDSN;
		std::string odbcUser;
		std::string odbcPassword;
	};

	struct WorldConfig
	{
		friend void from_json(const nlohmann::json& j, WorldConfig& config);

		int8_t id = -1;
	};

	class ServerConfig
	{
	public:
		void InitializeFromJson(const char* searchStartPath);

	public:
		LogConfig log;
		ExecutorConfig executor;
		GameDataConfig gameData;
		GameDBConfig gameDB;
		std::vector<WorldConfig> worlds;
	};
}
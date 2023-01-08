#include "server_config.h"

#include "lib/common/stacktrace_exception.h"

namespace cebreiro
{
	void from_json(const nlohmann::json& j, LogConfig& config)
	{
		j.at("console").get_to(config.console);
		j.at("dailyFile").get_to(config.dailyFile);
	}

	void from_json(const nlohmann::json& j, LogConfig::Console& config)
	{
		j.at("async").get_to(config.async);
		j.at("level").get_to(config.level);
	}

	void from_json(const nlohmann::json& j, LogConfig::DailyFile& config)
	{
		j.at("path").get_to(config.path);
		j.at("level").get_to(config.level);
	}

	void from_json(const nlohmann::json& j, ExecutorConfig& config)
	{
		j.at("networkConcurrency").get_to(config.networkConcurrency);
		j.at("dbConcurrency").get_to(config.dbConcurrency);
	}

	void from_json(const nlohmann::json& j, GameDataConfig& config)
	{
		j.at("path").get_to(config.path);
	}

	void from_json(const nlohmann::json& j, GameDBConfig& config)
	{
		j.at("odbcDSN").get_to(config.odbcDSN);
		j.at("odbcUser").get_to(config.odbcUser);
		j.at("odbcPassword").get_to(config.odbcPassword);
	}

	void from_json(const nlohmann::json& j, WorldConfig& config)
	{
		j.at("id").get_to(config.id);
	}

	void ServerConfig::InitializeFromJson(const char* searchStartPath)
	{
		auto tryInitializeFromFile = [this](const fs::path& path)
		{
			if (!fs::exists(path))
			{
				return false;
			}

			std::ifstream ifs(path);
			assert(ifs.is_open());

			nlohmann::json json = nlohmann::json::parse(ifs);

			log = json.at("log").get<LogConfig>();
			executor = json.at("executor").get<ExecutorConfig>();
			gameData = json.at("gameData").get<GameDataConfig>();
			gameDB = json.at("gameDB").get<GameDBConfig>();
			worlds = json.at("worlds").get<std::vector<WorldConfig>>();

			return true;
		};

		std::string fileName = "server_config.json";
		for (auto path = fs::path(searchStartPath); fs::exists(path) && path != path.parent_path(); path = path.parent_path())
		{
			if (tryInitializeFromFile(path / fileName))
			{
				return;
			}

			if (tryInitializeFromFile(path / "executable" / "game_server" / "config" / fileName))
			{
				return;
			}
		}

		throw StacktraceException(std::format("fail to find config file. file: {}", fileName));
	}
}

#pragma once
#include "lib/common/snowflake.h"
#include "lib/common/execution/future.h"
#include "lib/common/execution/thread_pool.h"
#include "config/server_constant.h"
#include "service/world_service_interface.h"

namespace cebreiro::gamedb
{
	class GameDB;
}

namespace cebreiro::world
{
	class WorldService : public IWorldService
	{
	public:
		WorldService(int8_t worldId, std::string address, gamedb::GameDB& gameDB);

		auto GenerateCharacterId() -> Future<int64_t> override;
		auto CheckCharacterNameUsable(std::string name) const -> Future<bool> override;
		auto CreateCharacter(gamedb::Character character) -> Future<bool> override;
		auto DeleteCharacter(int64_t cid) -> Future<bool> override;
		auto GetCharacters(int64_t aid) -> Future<std::vector<gamedb::Character>> override;

		auto Id() const -> int8_t override;
		auto Address() const -> std::string_view override;

	private:
		ThreadPool::Strand _strand;

		int8_t _worldId = -1;
		std::string _address;
		gamedb::GameDB& _gameDB;

		UniqueSnowflake<ServerConstant::TWEPOCH> _snowflake;
	};
}
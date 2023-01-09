#include "world_service.h"

#include "lib/common/execution/future_await.h"
#include "lib/common/execution/executor_await.h"
#include "lib/game_db/game_db.h"

namespace cebreiro::world
{
	WorldService::WorldService(int8_t worldId, std::string address, gamedb::GameDB& gameDB)
		: _strand(ThreadPool::GetInstance().MakeStrand())
		, _worldId(worldId)
		, _address(std::move(address))
		, _gameDB(gameDB)
		, _snowflake(worldId)
	{
	}

	auto WorldService::GenerateCharacterId() -> Future<int64_t>
	{
		co_await _strand;
		co_return static_cast<int64_t>(_snowflake.Generate());
	}

	auto WorldService::CheckCharacterNameUsable(std::string name) const -> Future<bool>
	{
		return _gameDB.CheckCharacterNameUsable(std::move(name));
	}

	auto WorldService::CreateCharacter(gamedb::Character character) -> Future<bool>
	{
		return _gameDB.CreateCharacter(std::move(character));
	}

	auto WorldService::DeleteCharacter(int64_t cid) -> Future<bool>
	{
		return _gameDB.DeleteCharacter(cid);
	}

	auto WorldService::GetCharacters(int64_t aid) -> Future<std::vector<gamedb::Character>>
	{
		std::vector<gamedb::Character> characters = co_await _gameDB.GetCharacters(aid);

		std::erase_if(characters, [this](const gamedb::Character& character)
			{
				return character.base.wid != _worldId;
			});

		co_return characters;
	}

	auto WorldService::Id() const -> int8_t
	{
		return _worldId;
	}

	auto WorldService::Address() const -> std::string_view
	{
		return _address;
	}
}

#pragma once
#include "lib/common/execution/future.h"
#include "lib/game_db/entity/character.h"

namespace cebreiro
{
	class IWorldService
	{
	public:
		virtual ~IWorldService() {}

		virtual auto GenerateCharacterId() -> Future<int64_t> = 0;

		virtual auto CheckCharacterNameUsable(std::string name) const -> Future<bool> = 0;
		virtual auto CreateCharacter(gamedb::Character character) -> Future<bool> = 0;
		virtual auto GetCharacters(int64_t aid) -> Future<std::vector<gamedb::Character>> = 0;

		virtual auto Id() const -> int8_t = 0;
		virtual auto Address() const -> std::string_view = 0;
	};
}
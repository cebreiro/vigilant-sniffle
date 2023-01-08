#pragma once
#include "lib/game_base/network/serialized_object.h"

namespace cebreiro::gamedata
{
	class GameDataSource;
}

namespace cebreiro::gamedb
{
	struct Character;
}

namespace cebreiro::gateway
{
	class CharacterAppearance
	{
	public:
		CharacterAppearance(const gamedata::GameDataSource& dataSource, const gamedb::Character& character);

		auto Serialize() const -> gamebase::SerializedObject;

	private:
		std::optional<int32_t> _hatModelId = std::nullopt;
		int32_t _hairModel = 0;
		int32_t _hairColor = 0;
		int32_t _skinColor = 0;
		int32_t _face = 0;

		int32_t _jacketId = 0;
		int32_t _glovesModelId = 0;
		int32_t _pantsId = 0;
		int32_t _shoesId = 0;
	};
}
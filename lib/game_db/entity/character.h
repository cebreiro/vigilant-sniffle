#pragma once
#include "lib/game_base/db/character.h"

namespace cebreiro::gamedb
{
	struct Character
	{
		gamebase::Character base = {};
		gamebase::CharacterStat stat = {};
		gamebase::CharacterJob job = {};
		std::vector<gamebase::CharacterItem> items;
		std::vector<gamebase::CharacterSkill> skills;
	};
}
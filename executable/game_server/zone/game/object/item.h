#pragma once
#include "zone/game/object/game_object.h"

namespace cebreiro::gamedata
{
	struct ItemCommon;
}

namespace cebreiro::zone
{
	class Item : public GameObject
	{
	public:
		Item(Zone& zone, GameObjectId id, const gamedata::ItemCommon& data);
		~Item();

	private:
		const gamedata::ItemCommon& _data;
	};
}
#include "item.h"

namespace cebreiro::zone
{
	Item::Item(Zone& zone, GameObjectId id, const gamedata::ItemCommon& data)
		: GameObject(zone, id)
		, _data(data)
	{
	}

	Item::~Item()
	{
	}
}

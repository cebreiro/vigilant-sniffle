#pragma once
#include "zone/game/object/game_object.h"

namespace cebreiro::network
{
	class Session;
}

namespace cebreiro::gamedb
{
	struct Character;
}

namespace cebreiro::zone
{
	class Player : public GameObject
	{
	public:
		Player(Zone& zone, GameObjectId id, const gamedb::Character& character, std::shared_ptr<network::Session> session);
		~Player();
	};
}
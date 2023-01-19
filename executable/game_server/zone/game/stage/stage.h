#pragma once
#include "zone/game/object/game_object_id.h"

namespace cebreiro::zone::msg
{
	struct ZoneEvent;
}

namespace cebreiro::zone
{
	class Controller;
	class Player;
	class GameObject;
}

namespace cebreiro::zone
{
	class Stage
	{
	public:
		void Tick(time_point_t now);

		bool SpawnPlayer(std::shared_ptr<Player> player);
		auto DespawnPlayer(GameObjectId id) -> std::shared_ptr<Player>;

		auto Find(GameObjectId id) -> GameObject*;
		auto Find(GameObjectId id) const -> const GameObject*;

		auto Id() const -> int32_t;

	private:
		auto FindTickObject(GameObjectId id) -> GameObject*;
		bool RemoveTickObject(GameObjectId id);

	private:
		std::vector<GameObject*> _tickObjects;
		std::unordered_map<GameObjectId, GameObject*> _objectIdIndexer;

		std::map<GameObjectId, std::shared_ptr<Player>> _players;
	};
}

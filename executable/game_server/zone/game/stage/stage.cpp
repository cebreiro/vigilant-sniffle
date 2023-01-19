#include "stage.h"

#include "zone/game/object/game_object.h"
#include "zone/game/object/player.h"

namespace cebreiro::zone
{
	void Stage::Tick(time_point_t now)
	{
		for (GameObject* tickObject : _tickObjects)
		{
			tickObject->Tick(now);
		}
	}

	bool Stage::SpawnPlayer(std::shared_ptr<Player> player)
	{
		if (_players.contains(player->Id()))
		{
			return false;
		}

		assert(FindTickObject(player->Id()) == nullptr);
		assert(!_objectIdIndexer.contains(player->Id()));

		_players[player->Id()] = player;
		_objectIdIndexer[player->Id()] = player.get();
		_tickObjects.push_back(player.get());

		return true;
	}

	auto Stage::DespawnPlayer(GameObjectId id) -> std::shared_ptr<Player>
	{
		auto iter = _players.find(id);
		if (iter == _players.end())
		{
			return {};
		}

		std::shared_ptr<Player> player = std::move(iter->second);
		_players.erase(iter);

		[[maybe_unused]] bool result = false;
		result = _objectIdIndexer.erase(id);
		assert(result);

		result = RemoveTickObject(id);
		assert(result);

		return player;
	}

	auto Stage::Find(GameObjectId id) -> GameObject*
	{
		auto iter = _objectIdIndexer.find(id);
		return iter != _objectIdIndexer.end() ? iter->second : nullptr;
	}

	auto Stage::Find(GameObjectId id) const -> const GameObject*
	{
		auto iter = _objectIdIndexer.find(id);
		return iter != _objectIdIndexer.end() ? iter->second : nullptr;
	}

	auto Stage::Id() const -> int32_t
	{
		return 10000;
	}

	auto Stage::FindTickObject(GameObjectId id) -> GameObject*
	{
		auto iter = sr::find_if(_tickObjects, [id](GameObject* object)
			{
				return object->Id() == id;
			});
		return iter != _tickObjects.end() ? *iter : nullptr;
	}

	bool Stage::RemoveTickObject(GameObjectId id)
	{
		return std::erase_if(_tickObjects, [id](GameObject* object)
			{
				return object->Id() == id;
			});
	}
}

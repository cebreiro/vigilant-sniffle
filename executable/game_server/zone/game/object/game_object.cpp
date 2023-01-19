#include "game_object.h"

#include "lib/game_service/service_locator_interface.h"
#include "zone/game/zone.h"
#include "zone/game/component/movement_component.h"
#include "zone/game/domain/slot/slot_container.h"

namespace cebreiro::zone
{
	GameObject::GameObject(Zone& zone, GameObjectId id)
		: _zone(zone)
		, _dataSource(_zone.GetServiceLocator().GameDataSource())
		, _id(id)
	{
	}

	GameObject::~GameObject()
	{
	}

	void GameObject::Tick(time_point_t now)
	{
		for (const std::shared_ptr<ComponentBase>& component : _components | srv::values)
		{
			component->Tick(now);
		}
	}

	auto GameObject::Id() const -> GameObjectId
	{
		return _id;
	}

	auto GameObject::MoverId() const -> int32_t
	{
		return Get<MovementComponent>().GetMoverId();
	}

	auto GameObject::Type() const -> type::Object
	{
		return _id.GetType();
	}

	auto GameObject::GetZone() -> Zone&
	{
		return _zone;
	}

	auto GameObject::GetZone() const -> const Zone&
	{
		return _zone;
	}

	auto GameObject::GetStage() -> Stage&
	{
		assert(_stage);
		return *_stage;
	}

	auto GameObject::GetStage() const -> const Stage&
	{
		assert(_stage);
		return *_stage;
	}

	auto GameObject::GetDataSource() const -> const gamedata::GameDataSource&
	{
		return _dataSource;
	}

	auto GameObject::GetController() -> Controller&
	{
		assert(_controller);
		return *_controller;
	}

	auto GameObject::GetController() const -> const Controller&
	{
		assert(_controller);
		return *_controller;
	}

	void GameObject::SetController(std::shared_ptr<Controller> controller)
	{
		assert(controller);
		_controller = std::move(controller);
	}

	void GameObject::SetStage(Stage* stage)
	{
		_stage = stage;
	}
}

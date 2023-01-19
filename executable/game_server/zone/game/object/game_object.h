#pragma once
#include "zone/game/component/component_base.h"
#include "zone/game/object/game_object_id.h"

namespace cebreiro::gamedata
{
	class GameDataSource;
}

namespace cebreiro::zone
{
	class Zone;
	class Stage;
	class ComponentBase;
	class Controller;
}

namespace cebreiro::zone
{
	class GameObject : public std::enable_shared_from_this<GameObject>
	{
	public:
		GameObject(Zone& zone, GameObjectId id);
		~GameObject();

		void Tick(time_point_t now);

		auto Id() const -> GameObjectId;
		auto MoverId() const -> int32_t;
		auto Type() const -> type::Object;

		auto GetZone() -> Zone&;
		auto GetZone() const -> const Zone&;
		auto GetStage() -> Stage&;
		auto GetStage() const -> const Stage&;
		auto GetDataSource() const -> const gamedata::GameDataSource&;
		auto GetController() -> Controller&;
		auto GetController() const -> const Controller&;

		void SetStage(Stage* stage);
		void SetController(std::shared_ptr<Controller> controller);

	public:
		template <GameComponent T>
		bool Add(std::shared_ptr<T> component);

		template <GameComponent T>
		bool Remove();

		template <GameComponent T>
		auto Find() -> T*;

		template <GameComponent T>
		auto Find() const -> const T*;

		template <GameComponent T>
		auto Get() -> T&;

		template <GameComponent T>
		auto Get() const -> const T&;

	private:
		Zone& _zone;
		Stage* _stage = nullptr;
		const gamedata::GameDataSource& _dataSource;
		std::shared_ptr<Controller> _controller;
		GameObjectId _id = {};
		boost::container::flat_map<int64_t, std::shared_ptr<ComponentBase>> _components;
	};

	template <GameComponent T>
	bool GameObject::Add(std::shared_ptr<T> component)
	{
		int64_t classId = ComponentBase::GetClassId<T>();

		return _components.try_emplace(classId, std::move(component)).second;
	}

	template <GameComponent T>
	bool GameObject::Remove()
	{
		int64_t classId = ComponentBase::GetClassId<T>();
		return _components.erase(classId);
	}

	template <GameComponent T>
	auto GameObject::Find() -> T*
	{
		int64_t classId = ComponentBase::GetClassId<T>();

		auto iter = _components.find(classId);
		return iter != _components.end() ? static_cast<T*>(iter->second.get()) : nullptr;
	}

	template <GameComponent T>
	auto GameObject::Find() const -> const T*
	{
		int64_t classId = ComponentBase::GetClassId<T>();

		auto iter = _components.find(classId);
		return iter != _components.end() ? static_cast<const T*>(iter->second.get()) : nullptr;
	}

	template <GameComponent T>
	auto GameObject::Get() -> T&
	{
		int64_t classId = ComponentBase::GetClassId<T>();

		auto iter = _components.find(classId);
		if (iter == _components.end())
		{
			throw StacktraceException(
				std::format("fail to find component from entity."));
		}

		return static_cast<T&>(*iter->second);
	}

	template <GameComponent T>
	auto GameObject::Get() const -> const T&
	{
		int64_t classId = ComponentBase::GetClassId<T>();

		auto iter = _components.find(classId);
		if (iter == _components.end())
		{
			throw StacktraceException(
				std::format("fail to find component from entity."));
		}

		return static_cast<const T&>(*iter->second);
	}
}

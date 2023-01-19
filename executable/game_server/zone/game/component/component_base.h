#pragma once
#include "lib/common/class_id.h"

namespace cebreiro::zone
{
	class GameObject;
}

namespace cebreiro::zone
{
	class ComponentBase
	{
	public:
		explicit ComponentBase(GameObject& object);
		virtual ~ComponentBase() = default;

		void Tick(time_point_t now);

		template <typename T>
		static auto GetClassId() -> int64_t;

	protected:
		void SetDoTick(bool value);

		GameObject& _object;

	private:
		virtual void OnTick(time_point_t now);

		bool _doTick = true;
	};

	template <typename T>
	concept GameComponent = std::derived_from<T, ComponentBase>;

	template <typename T>
	auto ComponentBase::GetClassId() -> int64_t
	{
		static_assert(GameComponent<T>, "invalid class type");

		return ClassId<ComponentBase, int64_t>::GetId<T>();
	}
}
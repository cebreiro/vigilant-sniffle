#pragma once
#include "lib/game_base/type/object.h"

namespace cebreiro::zone
{
	class GameObjectId
	{
	public:
		GameObjectId() = default;
		GameObjectId(type::Object type, int32_t id);

		auto GetType() const -> type::Object;
		auto GetTypeValue() const -> int32_t;
		auto GetValue() const -> int32_t;

		bool operator==(const GameObjectId& rhs) const;
		bool operator!=(const GameObjectId& rhs) const;
		bool operator<(const GameObjectId& rhs) const;

	private:
		type::Object _type = type::Object::None;
		int32_t _id = -1;
	};
}

namespace std
{
	template <>
	struct hash<cebreiro::zone::GameObjectId>
	{
		auto operator()(const cebreiro::zone::GameObjectId& id) const noexcept -> size_t
		{
			return std::hash<int32_t>()(id.GetValue());
		}
	};
}
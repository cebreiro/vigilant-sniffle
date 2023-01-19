#include "game_object_id.h"

namespace cebreiro::zone
{
	GameObjectId::GameObjectId(type::Object type, int32_t id)
		: _type(type)
		, _id(id)
	{
	}

	auto GameObjectId::GetType() const -> type::Object
	{
		return _type;
	}

	auto GameObjectId::GetTypeValue() const -> int32_t
	{
		return static_cast<int32_t>(_type);
	}

	auto GameObjectId::GetValue() const -> int32_t
	{
		return _id;
	}

	bool GameObjectId::operator==(const GameObjectId& rhs) const
	{
		return _type == rhs._type && _id == rhs._id;
	}

	bool GameObjectId::operator!=(const GameObjectId& rhs) const
	{
		return !operator==(rhs);
	}

	bool GameObjectId::operator<(const GameObjectId& rhs) const
	{
		return _id < rhs._id;
	}
}

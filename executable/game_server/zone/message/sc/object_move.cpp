#include "object_move.h"

#include "lib/game_base/network/packet_writer.h"
#include "zone/game/component/movement_component.h"
#include "zone/game/object/game_object.h"

namespace cebreiro::zone::msg
{
	ObjectMove::ObjectMove(const GameObject& gameObject)
		: _moverId(gameObject.MoverId())
		, _movement(gameObject.Get<MovementComponent>().GetMovement())
	{
	}

	auto ObjectMove::GetType() const -> SCMessageType
	{
		return SCMessageType::NMS_OBJECT_MOVE;
	}

	void ObjectMove::SerializeBody(gamebase::PacketWriter& writer) const
	{
		gamebase::SerializedObject object;
		{
			object.WriteInt32(_moverId);
			_movement.Serialize(object);
		}

		writer.WriteObject(object);
	}
}

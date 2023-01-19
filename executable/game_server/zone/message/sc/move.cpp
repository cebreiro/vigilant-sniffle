#include "move.h"

namespace cebreiro::zone::msg
{
	Move::Move(const GameObject& gameObject)
		: ObjectMove(gameObject)
	{
	}

	auto Move::GetType() const -> SCMessageType
	{
		return SCMessageType::NMS_MOVE;
	}
}

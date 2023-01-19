#include "force_move.h"

namespace cebreiro::zone::msg
{
	ForceMove::ForceMove(const GameObject& gameObject)
		: ObjectMove(gameObject)
	{
	}

	auto ForceMove::GetType() const -> SCMessageType
	{
		return SCMessageType::NMS_FORCE_MOVE;
	}
}

#pragma once
#include "zone/message/sc/object_move.h"

namespace cebreiro::zone::msg
{
	class ForceMove : public ObjectMove
	{
	public:
		explicit ForceMove(const GameObject& gameObject);

	private:
		auto GetType() const->SCMessageType override;
	};
}
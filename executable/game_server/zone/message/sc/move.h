#pragma once
#include "zone/message/sc/object_move.h"

namespace cebreiro::zone::msg
{
	class Move : public ObjectMove
	{
	public:
		explicit Move(const GameObject& gameObject);

	private:
		auto GetType() const -> SCMessageType override;
	};
}
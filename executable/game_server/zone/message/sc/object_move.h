#pragma once
#include "zone/message/sc/sc_message.h"
#include "zone/message/object/movement.h"

namespace cebreiro::zone
{
	class GameObject;
}

namespace cebreiro::zone::msg
{
	class ObjectMove : public SCMessage
	{
	public:
		explicit ObjectMove(const GameObject& gameObject);

	private:
		auto GetType() const -> SCMessageType override;
		void SerializeBody(gamebase::PacketWriter& writer) const override;

	private:
		int32_t _moverId = 0;
		Movement _movement = {};
	};
}
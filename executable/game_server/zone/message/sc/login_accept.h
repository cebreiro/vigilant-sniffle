#pragma once
#include "zone/message/sc/sc_message.h"
#include "zone/message/object/movement.h"
#include "zone/game/object/game_object_id.h"

namespace cebreiro::zone
{
	class GameObject;
}

namespace cebreiro::zone::msg
{
	class LoginAccept : public SCMessage
	{
	public:
		LoginAccept(const GameObject& object, int32_t zone, int32_t stage);

		auto GetId() const -> GameObjectId;
		auto GetStage() const -> int32_t;

	private:
		auto GetType() const -> SCMessageType override;
		void SerializeBody(gamebase::PacketWriter& writer) const override;

	private:
		int32_t _moverId = 0;
		Movement _movement;
		GameObjectId _id = {};
		int8_t _gender = 0;
		int32_t _zone = 0;
		int32_t _stage = 0;
	};
}
#pragma once
#include "zone/message/sc/sc_message.h"
#include "zone/message/object/movement.h"
#include "zone/game/object/game_object_id.h"

namespace cebreiro::zone
{
	class Player;
}

namespace cebreiro::zone::msg
{
	class UserInfoPlayer : public SCMessage
	{
	public:
		UserInfoPlayer(const Player& player, bool spawnEffect);

	private:
		auto GetType() const -> SCMessageType override;
		void SerializeBody(gamebase::PacketWriter& writer) const override;

	private:
		int32_t _moverId = 0;
		GameObjectId _id;
		int8_t _gender = 0;
		std::string _name;
		int8_t _armed = 0;
		bool _spawnEffect = false;
		int32_t unk = 0;
	};
}
#pragma once
#include "lib/game_base/network/packet_deserializable.h"
#include "zone/message/cs/cs_message_type.h"

namespace cebreiro::zone::msg
{
	struct SetDirectionRequest : gamebase::IPacketDeserializable
	{
		static constexpr CSMessageType TYPE = CSMessageType::NMC_REQ_SETDIRECTION;

		void Deserialize(gamebase::PacketReader& reader) override;

		float direction = 0.f;
	};
}
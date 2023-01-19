#pragma once
#include "lib/game_base/network/packet_deserializable.h"
#include "zone/message/cs/cs_message_type.h"
#include "zone/message/object/movement.h"

namespace cebreiro::zone::msg
{
	struct StopRequest : gamebase::IPacketDeserializable
	{
		static constexpr CSMessageType TYPE = CSMessageType::NMC_REQ_STOP;

		void Deserialize(gamebase::PacketReader& reader) override;

		Movement movement1;
		Movement movement2;
	};
}

#pragma once
#include "lib/game_base/network/packet_deserializable.h"
#include "zone/message/cs/cs_message_type.h"
#include "zone/game/event/event_type.h"

namespace cebreiro::zone::msg
{
	struct TriggerEvent : gamebase::IPacketDeserializable
	{
		static constexpr CSMessageType TYPE = CSMessageType::NMC_TRIGGER_EVENT;

		void Deserialize(gamebase::PacketReader& reader) override;

		// temp
		gamebase::PacketReader* reader = nullptr;
		EventType type = EventType::None;
	};
}
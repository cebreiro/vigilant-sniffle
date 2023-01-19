#include "trigger_event.h"

#include "lib/game_base/network/packet_reader.h"

namespace cebreiro::zone::msg
{
	void TriggerEvent::Deserialize(gamebase::PacketReader& reader1)
	{
		this->reader = &reader1;
		type = static_cast<EventType>(reader1.ReadInt8());
	}
}

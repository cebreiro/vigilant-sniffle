#include "character_select_request.h"

#include "lib/game_base/network/packet_reader.h"

namespace cebreiro::gateway
{
	void CharacterSelectRequest::Deserialize(gamebase::PacketReader& reader)
	{
		slot = static_cast<int8_t>(reader.ReadInt32());
	}
}

#include "character_name_check_request.h"

#include "lib/game_base/network/packet_reader.h"

namespace cebreiro::gateway
{
	void CharacterNameCheckRequest::Deserialize(gamebase::PacketReader& reader)
	{
		name = reader.ReadString();
	}
}

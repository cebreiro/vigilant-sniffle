#include "character_delete_request.h"

#include "lib/game_base/network/packet_reader.h"

namespace cebreiro::gateway
{
	bool CharacterDeleteRequest::IsValid() const
	{
		return slot >= 0 && slot <= 4;
	}

	void CharacterDeleteRequest::Deserialize(gamebase::PacketReader& reader)
	{
		slot = static_cast<int8_t>(reader.ReadInt32());
	}
}

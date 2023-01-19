#include "set_direction_request.h"

#include "lib/game_base/network/packet_reader.h"

namespace cebreiro::zone::msg
{
	void SetDirectionRequest::Deserialize(gamebase::PacketReader& reader)
	{
		direction = reader.ReadFloat32();
	}
}

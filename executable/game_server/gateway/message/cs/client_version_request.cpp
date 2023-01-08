#include "client_version_request.h"

#include "lib/game_base/network/packet_reader.h"

namespace cebreiro::gateway
{
	void ClientVersionRequest::Deserialize(gamebase::PacketReader& reader)
	{
		version = reader.ReadInt32();
	}
}

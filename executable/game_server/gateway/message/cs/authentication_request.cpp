#include "authentication_request.h"

#include "lib/game_base/network/packet_reader.h"

namespace cebreiro::gateway
{
	void AuthenticationRequest::Deserialize(gamebase::PacketReader& reader)
	{
		key2 = reader.ReadInt32();
		key1 = reader.ReadInt32();
		unk = reader.ReadInt64();

		// random bytes generated from client
		(void)reader.ReadObject();
	}
}

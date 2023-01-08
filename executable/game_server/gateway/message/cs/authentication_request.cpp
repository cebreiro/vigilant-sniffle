#include "authentication_request.h"

#include "lib/game_base/network/packet_reader.h"

namespace cebreiro::gateway
{
	void AuthenticationRequest::Deserialize(gamebase::PacketReader& reader)
	{
		int32_t key2 = reader.ReadInt32();
		int32_t key1 = reader.ReadInt32();

		token = { key1, key2 };
		unk = reader.ReadInt64();

		// random bytes generated from client
		(void)reader.ReadObject();
	}
}

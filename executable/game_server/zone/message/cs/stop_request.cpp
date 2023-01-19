#include "stop_request.h"

#include "lib/game_base/network/packet_reader.h"

namespace cebreiro::zone::msg
{
	void StopRequest::Deserialize(gamebase::PacketReader& reader)
	{
		StreamReader reader1 = reader.ReadObject();
		StreamReader reader2 = reader.ReadObject();

		movement1.Deserialize(reader1);
		movement2.Deserialize(reader2);
	}
}

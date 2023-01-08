#include "world_select_request.h"

#include "lib/common/stream/stream_reader.h"

namespace cebreiro::login
{
	void WorldSelectRequest::Deserialize(StreamReader& reader)
	{
		key1 = reader.ReadInt32();
		key2 = reader.ReadInt32();
		worldId = reader.ReadInt8();
	}
}

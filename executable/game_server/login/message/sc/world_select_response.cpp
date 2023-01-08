#include "world_select_response.h"

#include "lib/common/stream/stream_writer.h"

namespace cebreiro::login
{
	WorldSelectResponse::WorldSelectResponse(int8_t worldId, std::array<int32_t, 2> authToken)
		: _worldId(worldId)
		, _authToken(authToken)
	{
	}

	auto WorldSelectResponse::GetType() const -> SCMessageType
	{
		return SCMessageType::WorldSelectResponse;
	}

	auto WorldSelectResponse::GetBodySize() const -> size_t
	{
		return sizeof(_worldId) + (sizeof(decltype(_authToken)::value_type) * _authToken.max_size());
	}

	void WorldSelectResponse::SerializeBody(StreamWriter& writer) const
	{
		for (int32_t value : _authToken)
		{
			writer.WriteInt32(value);
		}

		writer.WriteInt8(_worldId);
	}
}

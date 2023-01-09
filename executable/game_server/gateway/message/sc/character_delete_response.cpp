#include "character_delete_response.h"

#include "lib/game_base/network/packet_writer.h"

namespace cebreiro::gateway
{
	CharacterDeleteResponse::CharacterDeleteResponse(bool result)
		: _result(result)
	{
	}

	auto CharacterDeleteResponse::GetType() const -> SCMessageType
	{
		return SCMessageType::CharacterDeleteResponse;
	}

	void CharacterDeleteResponse::SerializeBody(gamebase::PacketWriter& writer) const
	{
		writer.WriteInt32(!_result);
	}
}

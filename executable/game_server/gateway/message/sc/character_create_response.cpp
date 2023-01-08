#include "character_create_response.h"

#include "lib/game_base/network/packet_writer.h"

namespace cebreiro::gateway
{
	CharacterCreateResponse::CharacterCreateResponse(bool result)
		: _result(result)
	{
	}

	auto CharacterCreateResponse::GetType() const -> SCMessageType
	{
		return SCMessageType::CharacterCreateResponse;
	}

	void CharacterCreateResponse::SerializeBody(gamebase::PacketWriter& writer) const
	{
		writer.WriteInt32(!_result);
	}
}

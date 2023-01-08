#include "character_name_check_response.h"

#include "lib/game_base/network/packet_writer.h"

namespace cebreiro::gateway
{
	CharacterNameCheckResponse::CharacterNameCheckResponse(bool result, std::string_view name)
		: _result(result)
		, _name(std::move(name))
	{
	}

	auto CharacterNameCheckResponse::GetType() const -> SCMessageType
	{
		return SCMessageType::CharacterNameCheckResponse;
	}

	void CharacterNameCheckResponse::SerializeBody(gamebase::PacketWriter& writer) const
	{
		writer.WriteInt32(!_result);
		writer.WriteString(_name);
	}
}

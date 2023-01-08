#include "authentication_response.h"

#include "lib/game_base/network/packet_writer.h"

namespace cebreiro::gateway
{
	AuthenticationResponse::AuthenticationResponse(bool result)
		: _result(result)
	{
	}

	auto AuthenticationResponse::GetType() const -> SCMessageType
	{
		return SCMessageType::AuthenticationResponse;
	}

	void AuthenticationResponse::SerializeBody(gamebase::PacketWriter& writer) const
	{
		writer.WriteInt32(!_result);

		if (_result)
		{
			// 0x595F81
			writer.WriteString("unk_aabbccdd1122");
		}
	}
}

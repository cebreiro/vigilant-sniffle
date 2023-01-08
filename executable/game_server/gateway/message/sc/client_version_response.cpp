#include "client_version_response.h"

#include "lib/game_base/network/packet_writer.h"

namespace cebreiro::gateway
{
	ClientVersionResponse::ClientVersionResponse(bool result)
		: _result(result)
	{
	}

	auto ClientVersionResponse::GetType() const -> SCMessageType
	{
		return SCMessageType::ClientVersionResponse;
	}

	void ClientVersionResponse::SerializeBody(gamebase::PacketWriter& writer) const
	{
		writer.WriteInt32(!_result);
	}
}

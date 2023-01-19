#include "disconnect.h"

#include "lib/game_base/network/packet_writer.h"

namespace cebreiro::zone::msg
{
	Disconnect::Disconnect(std::string reason)
		: _reason(std::move(reason))
	{
	}

	auto Disconnect::GetType() const -> SCMessageType
	{
		return SCMessageType::NMS_DISCONNECT;
	}

	void Disconnect::SerializeBody(gamebase::PacketWriter& writer) const
	{
		writer.WriteInt32(0);
		writer.WriteString(_reason);
	}
}

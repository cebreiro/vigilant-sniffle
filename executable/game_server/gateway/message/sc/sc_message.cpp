#include "sc_message.h"

#include "lib/game_base/network/packet_writer.h"

namespace cebreiro::gateway
{
	SCMessage::~SCMessage()
	{
	}

	auto SCMessage::Serialize() const -> network::Buffer
	{
		gamebase::PacketWriter writer;
		writer.WriteInt32(static_cast<int32_t>(this->GetType()));
		this->SerializeBody(writer);

		return writer.MakeBuffer();
	}
}

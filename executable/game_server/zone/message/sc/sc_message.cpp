#include "sc_message.h"

#include "lib/game_base/network/packet_writer.h"


namespace cebreiro::zone
{
	SCMessage::~SCMessage()
	{
	}

	auto SCMessage::Serialize() const -> network::Buffer
	{
		gamebase::PacketWriter writer;
		writer.WriteInt8(static_cast<int8_t>(this->GetType()));
		this->SerializeBody(writer);

		return writer.MakeBuffer();
	}
}
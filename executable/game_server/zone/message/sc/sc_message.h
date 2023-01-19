#pragma once
#include "zone/message/sc/sc_message_type.h"
#include "lib/network/buffer.h"

namespace cebreiro::gamebase
{
	class PacketWriter;
}

namespace cebreiro::zone
{
	class SCMessage
	{
	public:
		SCMessage() = default;
		virtual ~SCMessage();

		auto Serialize() const -> network::Buffer;

	private:
		virtual auto GetType() const -> SCMessageType = 0;
		virtual void SerializeBody(gamebase::PacketWriter& writer) const = 0;
	};
}

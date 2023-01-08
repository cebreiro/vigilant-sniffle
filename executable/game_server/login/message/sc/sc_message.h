#pragma once
#include "login/message/sc/sc_message_type.h"
#include "lib/network/buffer.h"

namespace cebreiro
{
	class StreamWriter;
}

namespace cebreiro::login
{
	class SCMessage
	{
	public:
		SCMessage() = default;
		virtual ~SCMessage();

		auto Serialize() const -> network::Buffer;

	private:
		virtual auto GetType() const -> SCMessageType = 0;
		virtual auto GetBodySize() const -> size_t = 0;
		virtual void SerializeBody(StreamWriter& writer) const = 0;
	};
}
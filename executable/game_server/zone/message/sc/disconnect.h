#pragma once
#include "zone/message/sc/sc_message.h"

namespace cebreiro::zone::msg
{
	class Disconnect : public SCMessage
	{
	public:
		explicit Disconnect(std::string reason);

	private:
		auto GetType() const -> SCMessageType override;
		void SerializeBody(gamebase::PacketWriter& writer) const override;

		std::string _reason;
	};
}
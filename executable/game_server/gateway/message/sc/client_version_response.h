#pragma once
#include "gateway/message/sc/sc_message.h"

namespace cebreiro::gateway
{
	class ClientVersionResponse : public SCMessage
	{
	public:
		explicit ClientVersionResponse(bool result);

	private:
		auto GetType() const -> SCMessageType override;
		void SerializeBody(gamebase::PacketWriter& writer) const override;

	private:
		bool _result = false;
	};
}
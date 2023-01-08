#pragma once
#include "gateway/message/sc/sc_message.h"

namespace cebreiro::gateway
{
	class AuthenticationResponse : public SCMessage
	{
	public:
		explicit AuthenticationResponse(bool result);

	private:
		auto GetType() const -> SCMessageType override;
		void SerializeBody(gamebase::PacketWriter& writer) const override;

	private:
		bool _result = false;
	};
}
			
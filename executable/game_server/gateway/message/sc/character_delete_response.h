#pragma once
#include "gateway/message/sc/sc_message.h"

namespace cebreiro::gateway
{
	class CharacterDeleteResponse : public SCMessage
	{
	public:
		explicit CharacterDeleteResponse(bool result);

	private:
		auto GetType() const -> SCMessageType override;
		void SerializeBody(gamebase::PacketWriter& writer) const override;

	private:
		bool _result = false;
	};
}
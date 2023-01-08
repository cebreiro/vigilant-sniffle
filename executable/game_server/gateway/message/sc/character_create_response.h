#pragma once
#include "gateway/message/sc/sc_message.h"

namespace cebreiro::gateway
{
	class CharacterCreateResponse : public SCMessage
	{
	public:
		explicit CharacterCreateResponse(bool result);

	private:
		auto GetType() const -> SCMessageType override;
		void SerializeBody(gamebase::PacketWriter& writer) const override;

		bool _result;
	};
}
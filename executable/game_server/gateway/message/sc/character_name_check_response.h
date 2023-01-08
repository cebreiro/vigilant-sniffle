#pragma once
#include "gateway/message/sc/sc_message.h"

namespace cebreiro::gateway
{
	class CharacterNameCheckResponse : public SCMessage
	{
	public:
		CharacterNameCheckResponse(bool result, std::string_view name);

	private:
		auto GetType() const -> ::cebreiro::gateway::SCMessageType override;
		void SerializeBody(::cebreiro::gamebase::PacketWriter& writer) const override;

		bool _result = false;
		std::string_view _name;
	};
}
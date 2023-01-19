#pragma once
#include "zone/message/sc/sc_message.h"

namespace cebreiro::zone::msg
{
	class LoginReject : public SCMessage
	{
	public:
		explicit LoginReject(std::string reason);

	private:
		auto GetType() const -> ::cebreiro::zone::SCMessageType override;
		void SerializeBody(::cebreiro::gamebase::PacketWriter& writer) const override;

	private:
		std::string _reason;
	};
}
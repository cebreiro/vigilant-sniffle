#include "login_reject.h"

#include "lib/game_base/network/packet_writer.h"

namespace cebreiro::zone::msg
{
	LoginReject::LoginReject(std::string reason)
		: _reason(std::move(reason))
	{
	}

	auto LoginReject::GetType() const -> SCMessageType
	{
		return SCMessageType::NMS_LOGIN_REJECT;
	}

	void LoginReject::SerializeBody(gamebase::PacketWriter& writer) const
	{
		writer.WriteInt8(0);
		writer.WriteString(_reason);
	}
}

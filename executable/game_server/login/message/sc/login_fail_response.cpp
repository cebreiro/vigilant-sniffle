#include "login_fail_response.h"

#include "lib/common/stream/stream_writer.h"

namespace cebreiro::login
{
	LoginFailResponse::LoginFailResponse(LoginFailReason reason)
		: _reason(reason)
	{
	}

	auto LoginFailResponse::GetType() const -> SCMessageType
	{
		return SCMessageType::LoginFailResponse;
	}

	auto LoginFailResponse::GetBodySize() const -> size_t
	{
		return sizeof(_reason);
	}

	void LoginFailResponse::SerializeBody(StreamWriter& writer) const
	{
		writer.WriteInt32(static_cast<int32_t>(_reason));
	}
}

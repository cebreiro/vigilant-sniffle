#pragma once
#include "login/message/sc/sc_message.h"

namespace cebreiro::login
{
	class WorldSelectResponse : public SCMessage
	{
	public:
		WorldSelectResponse(int8_t worldId, std::array<int32_t, 2> authToken);

	private:
		auto GetType() const->SCMessageType override;
		auto GetBodySize() const->size_t override;
		void SerializeBody(StreamWriter& writer) const override;

	private:
		int8_t _worldId = -1;
		std::array<int32_t, 2> _authToken;
	};
}
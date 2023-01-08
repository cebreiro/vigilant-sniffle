#pragma once
#include "login/message/sc/sc_message.h"

namespace cebreiro::login
{
	class Hello : public SCMessage
	{
	public:
		Hello(uint32_t key1, uint32_t key2);

	private:
		auto GetType() const -> SCMessageType override;
		auto GetBodySize() const -> size_t override;
		void SerializeBody(StreamWriter& writer) const override;

	private:
		uint32_t _key1 = 0;
		uint32_t _key2 = 0;
	};
}
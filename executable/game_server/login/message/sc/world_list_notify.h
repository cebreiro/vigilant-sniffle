#pragma once
#include "login/message/sc/sc_message.h"

namespace cebreiro
{
	class IWorldService;
}

namespace cebreiro::login
{
	class WorldListNotify : public SCMessage
	{
	public:
		explicit WorldListNotify(const std::vector<IWorldService*>& worlds);

	private:
		auto GetType() const->SCMessageType override;
		auto GetBodySize() const->size_t override;
		void SerializeBody(StreamWriter& writer) const override;

	private:
		const std::vector<IWorldService*>& _worlds;
	};
}
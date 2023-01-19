#pragma once
#include "zone/game/controller/controller.h"

namespace cebreiro::network
{
	class Session;
}

namespace cebreiro::zone
{
	class RemotePlayerController : public Controller
	{
	public:
		explicit RemotePlayerController(std::shared_ptr<network::Session> session);

		void Send(const msg::ZoneEvent& event) override;

	private:
		std::shared_ptr<network::Session> _session;
	};
}
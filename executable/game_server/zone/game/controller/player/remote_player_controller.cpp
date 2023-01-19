#include "remote_player_controller.h"

#include "lib/network/session.h"

namespace cebreiro::zone
{
	RemotePlayerController::RemotePlayerController(std::shared_ptr<network::Session> session)
		: _session(std::move(session))
	{
		assert(_session);
	}

	void RemotePlayerController::Send(const msg::ZoneEvent& event)
	{
		(void)event;
		//_session->Send(event.Serialize());
	}
}

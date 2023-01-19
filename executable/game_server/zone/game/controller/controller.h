#pragma once

namespace cebreiro::zone::msg
{
	struct ZoneEvent;
}

namespace cebreiro::zone
{
	class Controller : public std::enable_shared_from_this<Controller>
	{
	public:
		virtual ~Controller();

		virtual void Send(const msg::ZoneEvent& event) = 0;
	};
}
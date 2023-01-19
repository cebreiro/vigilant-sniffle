#pragma once

namespace cebreiro::zone::msg
{
	ENUM_CLASS(EventType, int8_t,
		(None, -1)
		(Player, 0)
		(Zone, 1)
		(World, 2)
	)
}
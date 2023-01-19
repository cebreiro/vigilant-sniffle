#include "zone_event_type.h"

namespace cebreiro::zone::msg
{
	std::string ToString(ZoneEventType type)
	{
		switch (type)
		{
#define ZONE_EVENT_TYPE_ITEM(name, value) case ZoneEventType::##name: return #name;
			LIST_OF_ZONE_EVENT_TYPE
#undef ZONE_EVENT_TYPE_ITEM
		default:
			return std::format("unknown zone event[{}]", static_cast<int32_t>(type));
		}
	}
}

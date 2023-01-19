#include "zone_event_request_handler_factory.h"

#include "zone/game/event/zone/zone_event_request_handler.h"

namespace cebreiro::zone::msg
{
	using container_type = std::unordered_map<ZoneEventType, ZoneEventRequestHandlerFactory::value_type>;

	namespace
	{
		auto GetContainer() -> container_type&
		{
			static container_type instance;
			return instance;
		}
	}

	ZoneEventRequestHandlerFactory::Registry::Registry(ZoneEventType type, const value_type& factory)
	{
		Add(type, factory);
	}

	void ZoneEventRequestHandlerFactory::Add(ZoneEventType type, const value_type& value)
	{
		[[maybe_unused]] bool result = GetContainer().try_emplace(type, value).second;
	}

	auto ZoneEventRequestHandlerFactory::Create(ZoneEventType type, GameObjectId sourceId, GameObjectId targetId, gamebase::PacketReader& reader) -> std::optional<result_type>
	{
		container_type& container = GetContainer();

		auto iter = container.find(type);
		if (iter == container.end())
		{
			return std::nullopt;
		}

		return iter->second(type, sourceId, targetId, reader);
	}
}

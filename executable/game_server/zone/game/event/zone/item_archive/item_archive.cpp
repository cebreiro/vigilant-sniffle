#include "item_archive.h"

#include "lib/game_base/network/packet_reader.h"
#include "zone/game/event/zone/zone_event_request_handler_factory.h"
#include "zone/game/object/game_object.h"

namespace cebreiro::zone::msg
{
	[[maybe_unused]]
	static ZoneEventRequestHandlerFactory::AutoRegistry<ItemArchive> registry;

	void ItemArchive::Deserialize(gamebase::PacketReader& reader)
	{
		_subType = static_cast<ZoneEventType>(reader.ReadInt32());

		auto result = ZoneEventRequestHandlerFactory::Create(_subType, GetSourceId(), GetTargetId(), reader);
		if (result.has_value())
		{
			_subHandler = std::move(result.value());
		}
	}

	ItemArchive::ItemArchive(ZoneEventType type, GameObjectId sourceId, GameObjectId targetId)
		: ZoneEventRequestHandler(type, sourceId, targetId)
	{
	}

	void ItemArchive::HandleEvent(Zone& zone, Stage& stage, GameObject& source)
	{
		std::visit([&]<typename T>(const T& subHandler)
		{
			if (!subHandler)
			{
				return;
			}

			if constexpr (std::is_same_v<T, std::unique_ptr<ZoneEventRequestHandler>>)
			{
				subHandler->HandleEvent(zone, stage, source);
			}
			else if constexpr (std::is_same_v<T, std::unique_ptr<ZoneEventRequestAsyncHandler>>)
			{
				(void)subHandler->HandleEvent(zone, stage, source.shared_from_this());
			}
		}, _subHandler);
	}
}

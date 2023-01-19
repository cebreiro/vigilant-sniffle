#pragma once
#include "zone/game/event/zone/zone_event_type.h"
#include "zone/game/object/game_object_id.h"

namespace cebreiro::gamebase
{
	class PacketReader;
}

namespace cebreiro::zone::msg
{
	class ZoneEventRequestHandler;
	class ZoneEventRequestAsyncHandler;
}

namespace cebreiro::zone::msg
{
	class ZoneEventRequestHandlerFactory
	{
	public:
		using result_type = std::variant<std::unique_ptr<ZoneEventRequestHandler>, std::unique_ptr<ZoneEventRequestAsyncHandler>>;
		using value_type = std::function<result_type(ZoneEventType, GameObjectId, GameObjectId, gamebase::PacketReader&)>;

		struct Registry
		{
			Registry(ZoneEventType type, const value_type& factory);
		};

		template <typename T>
		struct AutoRegistry : Registry
		{
			AutoRegistry();
		};

	public:
		ZoneEventRequestHandlerFactory() = delete;

		static void Add(ZoneEventType type, const value_type& value);
		static auto Create(ZoneEventType type, GameObjectId sourceId, GameObjectId targetId, gamebase::PacketReader& reader)
			-> std::optional<result_type>;
	};

	template <typename T>
	ZoneEventRequestHandlerFactory::AutoRegistry<T>::AutoRegistry()
		: Registry(T::TYPE,
			[](ZoneEventType type, GameObjectId sourceId, GameObjectId targetId, gamebase::PacketReader& reader)
				-> result_type
			{
				assert(T::TYPE == type);

				auto handler = std::make_unique<T>(type, sourceId, targetId);
				handler->Deserialize(reader);

				return handler;
			})
	{
	}
}

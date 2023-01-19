#pragma once
#include "lib/game_base/network/packet_deserializable.h"
#include "zone/game/event/zone/zone_event_type.h"
#include "zone/game/object/game_object_id.h"

namespace cebreiro::gamebase
{
	class PacketReader;
}

namespace cebreiro::zone
{
	class Zone;
	class Stage;
	class GameObject;
}

namespace cebreiro::zone::msg
{
	class ZoneEventRequestHandler : public gamebase::IPacketDeserializable
	{
	public:
		ZoneEventRequestHandler(ZoneEventType type, GameObjectId sourceId, GameObjectId targetId);
		virtual ~ZoneEventRequestHandler();

		virtual void HandleEvent(Zone& zone, Stage& stage, GameObject& source) = 0;
		void Deserialize(gamebase::PacketReader& reader) override;

		auto Type() const -> ZoneEventType;
		auto GetSourceId() const -> GameObjectId;
		auto GetTargetId() const -> GameObjectId;

	private:
		ZoneEventType _type = ZoneEventType::None;
		GameObjectId _sourceId;
		GameObjectId _targetId;
	};

	class ZoneEventRequestAsyncHandler : public gamebase::IPacketDeserializable
	{
	public:
		ZoneEventRequestAsyncHandler(ZoneEventType type, GameObjectId sourceId, GameObjectId targetId);
		virtual ~ZoneEventRequestAsyncHandler();

		virtual auto HandleEvent(Zone& zone, Stage& stage, std::shared_ptr<GameObject> source) -> Future<void> = 0;
		void Deserialize(gamebase::PacketReader& reader) override;

		auto Type() const->ZoneEventType;
		auto GetSourceId() const->GameObjectId;
		auto GetTargetId() const->GameObjectId;

	private:
		ZoneEventType _type = ZoneEventType::None;
		GameObjectId _sourceId;
		GameObjectId _targetId;
	};
}
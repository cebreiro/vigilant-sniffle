#include "zone_event_request_handler.h"

#include "lib/game_base/network/packet_reader.h"

namespace cebreiro::zone::msg
{
	ZoneEventRequestHandler::ZoneEventRequestHandler(ZoneEventType type, GameObjectId sourceId, GameObjectId targetId)
		: _type(type)
		, _sourceId(sourceId)
		, _targetId(targetId)
	{
	}

	ZoneEventRequestHandler::~ZoneEventRequestHandler()
	{
	}

	void ZoneEventRequestHandler::Deserialize(gamebase::PacketReader& reader)
	{
		(void)reader;
	}

	auto ZoneEventRequestHandler::Type() const -> ZoneEventType
	{
		return _type;
	}

	auto ZoneEventRequestHandler::GetSourceId() const -> GameObjectId
	{
		return _sourceId;
	}

	auto ZoneEventRequestHandler::GetTargetId() const -> GameObjectId
	{
		return _targetId;
	}

	ZoneEventRequestAsyncHandler::ZoneEventRequestAsyncHandler(ZoneEventType type, GameObjectId sourceId, GameObjectId targetId)
		: _type(type)
		, _sourceId(sourceId)
		, _targetId(targetId)
	{
	}

	ZoneEventRequestAsyncHandler::~ZoneEventRequestAsyncHandler()
	{
	}

	void ZoneEventRequestAsyncHandler::Deserialize(gamebase::PacketReader& reader)
	{
		(void)reader;
	}

	auto ZoneEventRequestAsyncHandler::Type() const -> ZoneEventType
	{
		return _type;
	}

	auto ZoneEventRequestAsyncHandler::GetSourceId() const -> GameObjectId
	{
		return _sourceId;
	}

	auto ZoneEventRequestAsyncHandler::GetTargetId() const -> GameObjectId
	{
		return _targetId;
	}
}

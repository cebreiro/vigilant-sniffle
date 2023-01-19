#include "trigger_event_handler.h"

#include "lib/common/log/log_macro.h"
#include "lib/game_base/network/packet_reader.h"
#include "lib/game_service/service_locator_interface.h"
#include "lib/network/session.h"
#include "zone/game/zone.h"
#include "zone/game/event/zone/zone_event_request_handler.h"
#include "zone/game/event/zone/zone_event_request_handler_factory.h"
#include "zone/game/object/game_object_id.h"
#include "zone/server/zone_session_context.h"
#include "zone/server/handler/cs_message_handler_auto_registry.h"

namespace cebreiro::zone
{
	[[maybe_unused]]
	static CSMessageHandlerAutoRegistryT<TriggerEventHandler> registry;

	auto TriggerEventHandler::OnMessage(const IServiceLocator& locator, ZoneSessionContext& context,
		const msg::TriggerEvent& message) -> Future<void>
	{
		network::Session& session = *context.session;
		Zone& zone = context.zone;
		gamebase::PacketReader& reader = *message.reader;

		if (context.state != ZoneSessionState::Authorized)
		{
			co_return;
		}

		switch (message.type)
		{
		case msg::EventType::Player:
		{

		}
		break;
		case msg::EventType::Zone:
		{
			int32_t unk = reader.ReadInt32();
			GameObjectId target = [](gamebase::PacketReader& reader)
			{
				auto [low, high] = reader.ReadInt64();
				return GameObjectId(static_cast<type::Object>(high), low);
			}(reader);

			auto eventType = static_cast<msg::ZoneEventType>(reader.ReadInt32());

			if (unk != 0)
			{
				LOGD(locator.LogService(),
					std::format("new unk value found. unk: {}, sender[{}:{}], type: {}",
						unk, ToString(context.gameObjectId.GetType()), context.gameObjectId.GetValue(), msg::ToString(eventType)))
			}

			auto eventHandler = msg::ZoneEventRequestHandlerFactory::Create(eventType, context.gameObjectId, target, reader);

			if (eventHandler.has_value())
			{
				bool result = false;

				if (auto* handler = std::get_if<std::unique_ptr<msg::ZoneEventRequestHandler>>(&(*eventHandler)))
				{
					result = co_await zone.PostEvent(context.stage, std::move(*handler))
						.ConfigureAwait(context.strand);
				}
				else if (auto* asyncHandler = std::get_if<std::unique_ptr<msg::ZoneEventRequestAsyncHandler>>(&(*eventHandler)))
				{
					result = co_await zone.PostEvent(context.stage, std::move(*asyncHandler))
						.ConfigureAwait(context.strand);
				}
				else
				{
					assert(false);
				}

				if (!result)
				{
					LOGW(locator.LogService(),
						std::format("fail to handle zone event. event: {}, sender[{}:{}], session[{}:{}]",
							ToString(eventType),
							ToString(context.gameObjectId.GetType()), context.gameObjectId.GetValue(),
							session.Id().Value(), session.RemoteAddress()))
				}
			}
			else
			{
				LOGW(locator.LogService(),
					std::format("fail to find zone event factory. event: {}, bytes: {}, sender[{}:{}], session[{}:{}]",
						ToString(eventType), message.reader->GetDebugString(), 
						ToString(context.gameObjectId.GetType()), context.gameObjectId.GetValue(),
						session.Id().Value(), session.RemoteAddress()))
			}
		}
		break;
		case msg::EventType::World:
		{

		}
		break;
		default:
			LOGW(locator.LogService(), 
				std::format("unhandled trigger event. type: {}, bytes: {}, session[{}:{}]",
					ToString(message.type), message.reader->GetDebugString(), session.Id().Value(), session.RemoteAddress()))
		}

		co_return;
	}
}

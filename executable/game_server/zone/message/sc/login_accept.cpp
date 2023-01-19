#include "login_accept.h"

#include <boost/lexical_cast.hpp>

#include "lib/common/stream/stream_writer.h"
#include "lib/game_base/network/packet_writer.h"
#include "zone/game/component/movement_component.h"
#include "zone/game/object/game_object.h"

namespace cebreiro::zone::msg
{
	LoginAccept::LoginAccept(const GameObject& object, int32_t zone, int32_t stage)
		: _moverId(object.MoverId())
		, _movement(object.Get<MovementComponent>().GetMovement())
		, _id(object.Id())
		, _gender(0)
		, _zone(zone)
		, _stage(stage)
	{
	}

	auto LoginAccept::GetId() const -> GameObjectId
	{
		return _id;
	}

	auto LoginAccept::GetStage() const -> int32_t
	{
		return _stage;
	}

	auto LoginAccept::GetType() const -> SCMessageType
	{
		return SCMessageType::NMS_LOGIN_ACCEPT;
	}

	void LoginAccept::SerializeBody(gamebase::PacketWriter& writer) const
	{
		gamebase::SerializedObject object;
		{
			object.WriteInt32(_moverId);
			object.WriteInt32(0);

			_movement.Serialize(object);
		}

		writer.WriteObject(object);
		writer.WriteString(boost::lexical_cast<std::string>(_zone));
		writer.WriteInt32(_id.GetValue());
		writer.WriteInt32(_id.GetTypeValue()); // 0x4E6596, 서버 데이터 안 읽고 0x44C SlPlayer 로 하드코딩
		writer.WriteInt32(_gender);
		writer.WriteInt32(_stage);

		// 날씨? tick 처리?
		writer.WriteInt32(0);
		writer.WriteInt32(0); // 0x55555555, 0x11111111 넣으면 눈 옮 0x4E6560
		writer.WriteZeroByte(4);
	}
}

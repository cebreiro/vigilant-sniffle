#include "user_info_player.h"

#include "lib/game_base/network/packet_writer.h"
#include "zone/game/object/player.h"

namespace cebreiro::zone::msg
{
	UserInfoPlayer::UserInfoPlayer(const Player& player, bool spawnEffect)
		: _moverId(player.MoverId())
		, _id(player.Id())
		, _spawnEffect(spawnEffect)
	{
	}

	auto UserInfoPlayer::GetType() const -> SCMessageType
	{
		return SCMessageType::NMS_USERINFO;
	}

	void UserInfoPlayer::SerializeBody(gamebase::PacketWriter& writer) const
	{
		writer.WriteInt32(_moverId);
		writer.WriteInt32(_id.GetTypeValue());
		writer.WriteInt32(_id.GetValue());
		writer.WriteInt32(_gender);
		writer.WriteString(_name);
		writer.WriteInt8(_armed);
		writer.WriteInt8(!_spawnEffect);
		writer.WriteInt32(unk);
	}
}

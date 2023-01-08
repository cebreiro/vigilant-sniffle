#include "character_list_response.h"

#include "lib/game_base/network/packet_writer.h"
#include "lib/game_db/entity/character.h"
#include "gateway/message/object/character_appearance.h"
#include "gateway/message/object/character_data.h"

namespace cebreiro::gateway
{
	CharacterListResponse::CharacterListResponse(const gamedata::GameDataSource& dataSource,
		const std::vector<gamedb::Character>& characters)
		: _dataSource(dataSource)
		, _characters(characters)
	{
	}

	auto CharacterListResponse::GetType() const -> SCMessageType
	{
		return SCMessageType::CharacterListResponse;
	}

	void CharacterListResponse::SerializeBody(gamebase::PacketWriter& writer) const
	{
		writer.WriteInt32(0); // v4[92] 에 들어가고 0이 여야함
		writer.WriteInt32(static_cast<int32_t>(_characters.size()));
		writer.WriteInt32(0); // // 0x8003 에서 분기될 때 case , 값은 모름

		for (const gamedb::Character& character : _characters)
		{
			writer.WriteObject(CharacterAppearance(_dataSource, character).Serialize());
			writer.WriteObject(CharacterData(character).Serialize());
		}
	}
}

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
		writer.WriteInt32(0); // v4[92] �� ���� 0�� ������
		writer.WriteInt32(static_cast<int32_t>(_characters.size()));
		writer.WriteInt32(0); // // 0x8003 ���� �б�� �� case , ���� ��

		for (const gamedb::Character& character : _characters)
		{
			writer.WriteObject(CharacterAppearance(_dataSource, character).Serialize());
			writer.WriteObject(CharacterData(character).Serialize());
		}
	}
}

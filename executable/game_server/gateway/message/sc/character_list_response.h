#pragma once
#include "gateway/message/sc/sc_message.h"

namespace cebreiro::gamedata
{
	class GameDataSource;
}

namespace cebreiro::gamedb
{
	struct Character;
}

namespace cebreiro::gateway
{
	class CharacterListResponse : public SCMessage
	{
	public:
		CharacterListResponse(const gamedata::GameDataSource& dataSource, const std::vector<gamedb::Character>& characters);

	private:
		auto GetType() const->SCMessageType override;
		void SerializeBody(gamebase::PacketWriter& writer) const override;

	private:
		const gamedata::GameDataSource& _dataSource;
		const std::vector<gamedb::Character>& _characters;
	};
}
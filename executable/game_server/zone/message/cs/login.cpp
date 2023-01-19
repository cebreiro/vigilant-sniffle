#include "login.h"

#include "lib/game_base/network/packet_reader.h"

namespace cebreiro::zone::msg
{
	void Login::Deserialize(gamebase::PacketReader& reader)
	{
		// unk
		(void)reader.ReadObject();

		StreamReader temp = reader.ReadObject();
		gamebase::PacketReader tokenReader(std::span(temp.GetData(), temp.GetSize()), 2);

		token.Deserialize(tokenReader);
	}

	void Login::Token::Deserialize(gamebase::PacketReader& reader)
	{
		auth = reader.ReadInt32();
		key = reader.ReadString();
	}
}

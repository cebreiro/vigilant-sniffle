#pragma once
#include "lib/game_base/network/packet_deserializable.h"
#include "zone/message/cs/cs_message_type.h"

namespace cebreiro::zone::msg
{
	struct Login : gamebase::IPacketDeserializable
	{
		static constexpr CSMessageType TYPE = CSMessageType::NMC_LOGIN;

		void Deserialize(gamebase::PacketReader& reader) override;

		struct Token : gamebase::IPacketDeserializable
		{
			void Deserialize(gamebase::PacketReader& reader) override;

			std::string key;
			int32_t auth = 0;
		};

		Token token;
	};
}
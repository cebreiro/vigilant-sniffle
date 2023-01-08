#pragma once
#include "lib/common/stream/deserializable.h"
#include "login/message/cs/cs_message_type.h"

namespace cebreiro::login
{
	struct LoginRequest : IDeserializable
	{
		static constexpr CSMessageType TYPE = CSMessageType::LoginRequest;

		void Deserialize(StreamReader& reader) override;

		std::string account;
		std::string password;
	};
}
#pragma once
#include "gateway/message/sc/sc_message.h"
#include "gateway/message/object/end_point.h"

namespace cebreiro::gateway
{
	class CharacterSelectResponse : public SCMessage
	{
		CharacterSelectResponse(bool success, int32_t auth, std::string key, EndPoint destination);

	public:
		static auto Success(int32_t auth, std::string key, EndPoint destination) -> CharacterSelectResponse;
		static auto Failure() -> CharacterSelectResponse;

	private:
		auto GetType() const->SCMessageType override;
		void SerializeBody(gamebase::PacketWriter& writer) const override;

		bool _success;
		int32_t _auth = 0;
		std::string _key;
		EndPoint _destination;
	};
}

#include "character_select_response.h"

#include "lib/game_base/network/packet_writer.h"

namespace cebreiro::gateway
{
	CharacterSelectResponse::CharacterSelectResponse(bool success, int32_t auth, std::string key, EndPoint destination)
		: _success(success)
		, _auth(auth)
		, _key(std::move(key))
		, _destination(std::move(destination))
	{
	}

	auto CharacterSelectResponse::Success(int32_t auth, std::string key,
		EndPoint destination) -> CharacterSelectResponse
	{
		return CharacterSelectResponse(true, auth, std::move(key), std::move(destination));
	}

	auto CharacterSelectResponse::Failure() -> CharacterSelectResponse
	{
		return CharacterSelectResponse(false, 0, {}, {});
	}

	auto CharacterSelectResponse::GetType() const -> SCMessageType
	{
		return SCMessageType::CharacterSelectResponse;
	}

	void CharacterSelectResponse::SerializeBody(gamebase::PacketWriter& writer) const
	{
		writer.WriteInt32(!_success);
		writer.WriteInt32(_auth);
		writer.WriteString(_key);
		writer.WriteObject(_destination.Serialize());
	}
}

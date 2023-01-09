#include "world_list_notify.h"

#include "lib/common/stream/stream_writer.h"
#include "lib/network/utility.h"
#include "lib/game_service/world/world_service_interface.h"

namespace cebreiro::login
{
	WorldListNotify::WorldListNotify(const std::vector<IWorldService*>& worlds)
		: _worlds(worlds)
	{
	}

	auto WorldListNotify::GetType() const -> SCMessageType
	{
		return SCMessageType::WorldListNotify;
	}

	auto WorldListNotify::GetBodySize() const -> size_t
	{
		return 1 + _worlds.size() * (1 + 4 + 4);
	}

	void WorldListNotify::SerializeBody(StreamWriter& writer) const
	{
		writer.WriteUInt8(static_cast<uint8_t>(_worlds.size()));

		for (const IWorldService* world : _worlds)
		{
			writer.WriteInt8(world->Id());

			// 일단 로컬에서 처리하니 나중에 확인
			writer.WriteInt32(network::AddressToBinaryForm(world->Address())); // source ?
			writer.WriteInt32(network::AddressToBinaryForm(world->Address())); // dest ?
		}
	}
}

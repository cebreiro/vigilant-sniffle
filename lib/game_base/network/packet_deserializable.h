#pragma once

namespace cebreiro::gamebase
{
	class PacketReader;

	struct IPacketDeserializable
	{
		virtual ~IPacketDeserializable() = default;

		virtual void Deserialize(PacketReader& reader) = 0;
	};
}
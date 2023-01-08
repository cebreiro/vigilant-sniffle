#pragma once

namespace cebreiro::gamebase
{
	class PacketWriter;

	struct IPacketSerializable
	{
		virtual ~IPacketSerializable() = default;

		virtual void Serialize(PacketWriter& writer) const = 0;
	};
}
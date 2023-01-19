#include "movement.h"

#include "lib/common/stream/stream_writer.h"

namespace cebreiro::zone
{
	Movement::Movement(StreamReader& reader)
	{
		Deserialize(reader);
	}

	auto Movement::Serialize() const -> gamebase::SerializedObject
	{
		gamebase::SerializedObject object;
		Serialize(object);

		return object;
	}

	void Movement::Serialize(gamebase::SerializedObject& object) const
	{
		object.WriteFloat32(position.GetX());
		object.WriteFloat32(position.GetY());
		object.WriteFloat32(direction);
		object.WriteFloat32(speed);
		object.WriteFloat32(unk1);
		object.WriteFloat32(destPosition.GetX());
		object.WriteFloat32(destPosition.GetY());
		object.WriteInt16(unk2);
		object.WriteInt16(unk3);
	}

	void Movement::Deserialize(StreamReader& reader)
	{
		position.SetX(reader.ReadFloat32());
		position.SetY(reader.ReadFloat32());
		direction = reader.ReadFloat32();
		speed = reader.ReadFloat32();
		unk1 = reader.ReadFloat32();
		destPosition.SetX(reader.ReadFloat32());
		destPosition.SetY(reader.ReadFloat32());
		unk2 = reader.ReadInt16();
		unk3 = reader.ReadInt16();
	}

	bool Movement::IsMoving() const
	{
		return unk3 == 0x10;
	}

	void Movement::SetMoving(bool value)
	{
		unk3 = value ? 0x10 : 0;
	}
}

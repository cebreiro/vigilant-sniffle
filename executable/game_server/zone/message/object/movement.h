#pragma once
#include "lib/common/math/vector.h"
#include "lib/common/stream/deserializable.h"
#include "lib/common/stream/stream_reader.h"
#include "lib/game_base/network/serialized_object.h"

namespace cebreiro::zone
{
	struct Movement : IDeserializable
	{
		Movement() = default;
		explicit Movement(StreamReader& reader);

		auto Serialize() const -> gamebase::SerializedObject;
		void Serialize(gamebase::SerializedObject& object) const;
		void Deserialize(StreamReader& reader) override;

		bool IsMoving() const;
		void SetMoving(bool value);

		Vector3D position = { 0.f, 0.f, 0.f };
		float direction = 0.f;
		float speed = 1.f;
		float unk1 = 0.f;
		Vector3D destPosition = { 0.f, 0.f, 0.f };
		int16_t unk2 = 0;
		int16_t unk3 = 0; // maybe move flag. 0: stop, 0x10: move
	};
}

#pragma once
#include "lib/game_base/network/serialized_object.h"

namespace cebreiro::gamedb
{
	struct Character;
}

namespace cebreiro::gateway
{
	class CharacterData
	{
	public:
		explicit CharacterData(const gamedb::Character& character);

		auto Serialize() const -> gamebase::SerializedObject;

	private:
		std::array<char, 20> _name = {};
		std::array<char, 4> _zone = {};
		int32_t _job1 = 0;
		int32_t _job2 = 0;
		int8_t _slot = 0;
		int8_t _arms = 0;
		int8_t _gender = 0;
		int32_t _charLevel = 0;
	};
}
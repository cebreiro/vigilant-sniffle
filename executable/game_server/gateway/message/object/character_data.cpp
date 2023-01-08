#include "character_data.h"

#include <boost/lexical_cast.hpp>

#include "lib/game_db/entity/character.h"

namespace cebreiro::gateway
{
	CharacterData::CharacterData(const gamedb::Character& character)
		: _job1(character.job.job1)
		, _job2(character.job.job2)
		, _slot(character.base.slot)
		, _arms(character.base.arms)
		, _gender(character.stat.gender)
		, _charLevel(character.stat.chr_lv)
	{
		const std::string& name = character.base.name;
		size_t nameCount = std::min(name.size(), _name.max_size());

		std::copy_n(name.data(), nameCount, _name.begin());

		const std::string& zone = boost::lexical_cast<std::string>(character.base.zone);
		size_t zoneCount = std::min(zone.size(), _zone.max_size());

		std::copy_n(zone.data(), zoneCount, _zone.begin());
	}

	auto CharacterData::Serialize() const -> gamebase::SerializedObject
	{
		gamebase::SerializedObject object;

		object.WriteBytes(_name.data(), _name.max_size()); //32
		object.WriteZeroBytes(12);

		object.WriteZeroBytes(32); //32 ~64

		object.WriteBytes(_zone.data(), _zone.max_size()); //32 ~96
		object.WriteZeroBytes(28);

		object.WriteZeroBytes(32); //32 ~128

		object.WriteZeroBytes(28);
		object.WriteInt32(_job2 != 0 ? _job2 : _job1); //32

		object.WriteInt8(_arms); // ���� ��� �ֱ�
		object.WriteInt32(0);
		object.WriteInt8(_slot);
		object.WriteInt32(0); // gm_level
		object.WriteInt8(true); // true �� ��� jacket, pants, shoes �� itemid �� �ް�, false�� ��� modelID�� �޴´�
		object.WriteZeroBytes(5); // ������� 16����Ʈ


		object.WriteInt32(0); // ���Կ� ������ ���� -> Ŭ�󿡼� Ư�� �κ� patch �� ��� ����
		object.WriteInt32(0); // ���Կ� ������ ����
		object.WriteZeroBytes(20);
		object.WriteZeroBytes(20);
		object.WriteZeroBytes(24);
		object.WriteInt32(_gender);
		object.WriteInt32(_charLevel);

		return object;
	}
}

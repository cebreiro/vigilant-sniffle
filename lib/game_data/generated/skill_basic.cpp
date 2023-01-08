/**********************************************************
         AUTO GENERATED FILE BY sox_code_generator
                   DO NOT EDIT THIS FILE
**********************************************************/
#include "skill_basic.h"

#include "lib/common/stream/stream_reader.h"
#include "lib/game_base/data/sox/sox_file.h"
#include "lib/game_data/game_data_registry.h"

namespace cebreiro::gamedata
{
	[[maybe_unused]]
	static GameDataRegistry<SkillBasicTable> registry;

	SkillBasic::SkillBasic(StreamReader& reader)
	{
		index = reader.ReadInt32();
		name = reader.ReadString(reader.ReadUInt16());
		routineId = reader.ReadInt32();
		abilityType = reader.ReadInt32();
		job1 = reader.ReadInt32();
		job2 = reader.ReadInt32();
		job3 = reader.ReadInt32();
		degree = reader.ReadInt32();
		maxLevel = reader.ReadInt32();
		delayId = reader.ReadInt32();
		canSubjob = reader.ReadInt32();
		levelQualification = reader.ReadInt32();
		ability1Qualification = reader.ReadInt32();
		ability1Level = reader.ReadInt32();
		ability2Qualification = reader.ReadInt32();
		ability2Level = reader.ReadInt32();
		passive = reader.ReadInt32();
		spConsumption = reader.ReadInt32();
		spConsumptionDelay = reader.ReadInt32();
		furyOnly = reader.ReadInt32();
		requireItem = reader.ReadInt32();
		requireItemCount = reader.ReadInt32();
		motionSpeed = reader.ReadFloat32();
		needWeapon = reader.ReadInt32();
		delayType = reader.ReadInt32();
		delayTime = reader.ReadInt32();
		useType = reader.ReadInt32();
		applyTargetType = reader.ReadInt32();
		applyDamageType = reader.ReadInt32();
		damageLength = reader.ReadInt32();
		damageLength2 = reader.ReadInt32();
		damageMaxcount = reader.ReadInt32();
		cancelable = reader.ReadInt32();
		useRange = reader.ReadInt32();
		addWeaponRange = reader.ReadInt32();
		applyCasting = reader.ReadInt32();
		castingDelay = reader.ReadInt32();
		applyCharging = reader.ReadInt32();
		chargingDelay = reader.ReadInt32();
		damageMotionType = reader.ReadInt32();
		effect1 = reader.ReadInt32();
		effect1Type = reader.ReadInt32();
		effect1Reserved1 = reader.ReadInt32();
		effect1Reserved2 = reader.ReadInt32();
		effect1Reserved3 = reader.ReadInt32();
		effect1Reserved4 = reader.ReadInt32();
		effect1Reserved5 = reader.ReadInt32();
		effect1Reserved6 = reader.ReadInt32();
		effect1Reserved7 = reader.ReadInt32();
		effect1Reserved8 = reader.ReadInt32();
		effect1Reserved9 = reader.ReadInt32();
		effect1Reserved10 = reader.ReadInt32();
		effect1Reserved11 = reader.ReadInt32();
		effect1Reserved12 = reader.ReadInt32();
		effect1HopType = reader.ReadInt32();
		effect1HopA = reader.ReadInt32();
		effect1HopB = reader.ReadInt32();
		effect2 = reader.ReadInt32();
		effect2Type = reader.ReadInt32();
		effect2Reserved1 = reader.ReadInt32();
		effect2Reserved2 = reader.ReadInt32();
		effect2Reserved3 = reader.ReadInt32();
		effect2Reserved4 = reader.ReadInt32();
		effect2Reserved5 = reader.ReadInt32();
		effect2Reserved6 = reader.ReadInt32();
		effect2Reserved7 = reader.ReadInt32();
		effect2Reserved8 = reader.ReadInt32();
		effect2Reserved9 = reader.ReadInt32();
		effect2Reserved10 = reader.ReadInt32();
		effect2Reserved11 = reader.ReadInt32();
		effect2Reserved12 = reader.ReadInt32();
		effect2HopType = reader.ReadInt32();
		effect2HopA = reader.ReadInt32();
		effect2HopB = reader.ReadInt32();
		effect3 = reader.ReadInt32();
		effect3Type = reader.ReadInt32();
		effect3Reserved1 = reader.ReadInt32();
		effect3Reserved2 = reader.ReadInt32();
		effect3Reserved3 = reader.ReadInt32();
		effect3Reserved4 = reader.ReadInt32();
		effect3Reserved5 = reader.ReadInt32();
		effect3Reserved6 = reader.ReadInt32();
		effect3Reserved7 = reader.ReadInt32();
		effect3Reserved8 = reader.ReadInt32();
		effect3Reserved9 = reader.ReadInt32();
		effect3Reserved10 = reader.ReadInt32();
		effect3Reserved11 = reader.ReadInt32();
		effect3Reserved12 = reader.ReadInt32();
		effect3HopType = reader.ReadInt32();
		effect3HopA = reader.ReadInt32();
		effect3HopB = reader.ReadInt32();
		effect4 = reader.ReadInt32();
		effect4Type = reader.ReadInt32();
		effect4Reserved1 = reader.ReadInt32();
		effect4Reserved2 = reader.ReadInt32();
		effect4Reserved3 = reader.ReadInt32();
		effect4Reserved4 = reader.ReadInt32();
		effect4Reserved5 = reader.ReadInt32();
		effect4Reserved6 = reader.ReadInt32();
		effect4Reserved7 = reader.ReadInt32();
		effect4Reserved8 = reader.ReadInt32();
		effect4Reserved9 = reader.ReadInt32();
		effect4Reserved10 = reader.ReadInt32();
		effect4Reserved11 = reader.ReadInt32();
		effect4Reserved12 = reader.ReadInt32();
		effect4HopType = reader.ReadInt32();
		effect4HopA = reader.ReadInt32();
		effect4HopB = reader.ReadInt32();
	}

	void SkillBasicTable::LoadFromFile(const std::filesystem::path& path)
	{
		gamebase::SoxFile fileData(path / "skill_basic.sox");
		StreamReader reader(fileData.gameData.data(), fileData.gameData.size());

		_vector.reserve(fileData.rowCount);
		for (int32_t i = 0; i < fileData.rowCount; ++i)
		{
			_vector.emplace_back(reader);
		}

		for (const SkillBasic& data : _vector)
		{
			_umap[data.index] = &data;
		}
	}

	auto SkillBasicTable::Find(int32_t index) const -> const SkillBasic*
	{
		auto iter = _umap.find(index);
		return iter != _umap.end() ? iter->second : nullptr;
	}

	auto SkillBasicTable::Get() const -> const std::vector<SkillBasic>&
	{
		return _vector;
	}
}

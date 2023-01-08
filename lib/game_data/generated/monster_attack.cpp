/**********************************************************
         AUTO GENERATED FILE BY sox_code_generator
                   DO NOT EDIT THIS FILE
**********************************************************/
#include "monster_attack.h"

#include "lib/common/stream/stream_reader.h"
#include "lib/game_base/data/sox/sox_file.h"
#include "lib/game_data/game_data_registry.h"

namespace cebreiro::gamedata
{
	[[maybe_unused]]
	static GameDataRegistry<MonsterAttackTable> registry;

	MonsterAttack::MonsterAttack(StreamReader& reader)
	{
		index = reader.ReadInt32();
		attackType = reader.ReadInt32();
		attackPercent = reader.ReadInt32();
		attackRange = reader.ReadInt32();
		attackDamageFactor = reader.ReadFloat32();
		attackDivDamage = reader.ReadInt32();
		attackDivDamageDelay = reader.ReadInt32();
		attackEffectRange = reader.ReadInt32();
		attackReserved1 = reader.ReadInt32();
		attackReserved2 = reader.ReadInt32();
		attackReserved3 = reader.ReadInt32();
		attackBulletID = reader.ReadInt32();
		attackConditionID = reader.ReadInt32();
		attackConditionKeepTime = reader.ReadInt32();
		attackConditionProbability = reader.ReadInt32();
		attackConditionReserved1 = reader.ReadInt32();
		attackConditionReserved2 = reader.ReadInt32();
		attackAniPartID = reader.ReadInt32();
		attackEndFrame = reader.ReadInt32();
		attackDelay = reader.ReadInt32();
		attackBeatFrame = reader.ReadInt32();
		attackFxGroupID = reader.ReadInt32();
		attackSoundFileID = reader.ReadInt32();
		skill1Type = reader.ReadInt32();
		skill1Percent = reader.ReadInt32();
		skill1Range = reader.ReadInt32();
		skill1CoolTime = reader.ReadInt32();
		skill1LV = reader.ReadInt32();
		skill1AniPartID = reader.ReadInt32();
		skill1EndFrame = reader.ReadInt32();
		skill1Delay = reader.ReadInt32();
		skill1BeatFrame = reader.ReadInt32();
		skill1AbilityID = reader.ReadInt32();
		skill2Type = reader.ReadInt32();
		skill2Percent = reader.ReadInt32();
		skill2Range = reader.ReadInt32();
		skill2CoolTime = reader.ReadInt32();
		skill2LV = reader.ReadInt32();
		skill2AniPartID = reader.ReadInt32();
		skill2EndFrame = reader.ReadInt32();
		skill2Delay = reader.ReadInt32();
		skill2BeatFrame = reader.ReadInt32();
		skill2AbilityID = reader.ReadInt32();
		skill3Type = reader.ReadInt32();
		skill3Percent = reader.ReadInt32();
		skill3Range = reader.ReadInt32();
		skill3CoolTime = reader.ReadInt32();
		skill3LV = reader.ReadInt32();
		skill3AniPartID = reader.ReadInt32();
		skill3EndFrame = reader.ReadInt32();
		skill3Delay = reader.ReadInt32();
		skill3BeatFrame = reader.ReadInt32();
		skill3AbilityID = reader.ReadInt32();
		passive1Percent = reader.ReadInt32();
		passive1LV = reader.ReadInt32();
		passive1AddExp = reader.ReadInt32();
		passive1ID = reader.ReadInt32();
		passive1ExtraMoney = reader.ReadInt32();
		passive2Percent = reader.ReadInt32();
		passive2LV = reader.ReadInt32();
		passive2AddExp = reader.ReadInt32();
		passive2ID = reader.ReadInt32();
		passive2ExtraMoney = reader.ReadInt32();
		passive3Percent = reader.ReadInt32();
		passive3LV = reader.ReadInt32();
		passive3AddExp = reader.ReadInt32();
		passive3ID = reader.ReadInt32();
		passive3ExtraMoney = reader.ReadInt32();
	}

	void MonsterAttackTable::LoadFromFile(const std::filesystem::path& path)
	{
		gamebase::SoxFile fileData(path / "MONSTER_ATTACK.sox");
		StreamReader reader(fileData.gameData.data(), fileData.gameData.size());

		_vector.reserve(fileData.rowCount);
		for (int32_t i = 0; i < fileData.rowCount; ++i)
		{
			_vector.emplace_back(reader);
		}

		for (const MonsterAttack& data : _vector)
		{
			_umap[data.index] = &data;
		}
	}

	auto MonsterAttackTable::Find(int32_t index) const -> const MonsterAttack*
	{
		auto iter = _umap.find(index);
		return iter != _umap.end() ? iter->second : nullptr;
	}

	auto MonsterAttackTable::Get() const -> const std::vector<MonsterAttack>&
	{
		return _vector;
	}
}

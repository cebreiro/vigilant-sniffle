/**********************************************************
         AUTO GENERATED FILE BY sox_code_generator
                   DO NOT EDIT THIS FILE
**********************************************************/
#pragma once
#include <cstdint>
#include <string>
#include <vector>
#include <unordered_map>
#include <filesystem>
#include "lib/game_data/game_data_table.h"

namespace cebreiro { class StreamReader; }

namespace cebreiro::gamedata
{
	struct MonsterAttack
	{
		MonsterAttack() = default;
		explicit MonsterAttack(StreamReader& reader);

		int32_t index = 0;
		int32_t attackType = 0;
		int32_t attackPercent = 0;
		int32_t attackRange = 0;
		float attackDamageFactor = 0.f;
		int32_t attackDivDamage = 0;
		int32_t attackDivDamageDelay = 0;
		int32_t attackEffectRange = 0;
		int32_t attackReserved1 = 0;
		int32_t attackReserved2 = 0;
		int32_t attackReserved3 = 0;
		int32_t attackBulletID = 0;
		int32_t attackConditionID = 0;
		int32_t attackConditionKeepTime = 0;
		int32_t attackConditionProbability = 0;
		int32_t attackConditionReserved1 = 0;
		int32_t attackConditionReserved2 = 0;
		int32_t attackAniPartID = 0;
		int32_t attackEndFrame = 0;
		int32_t attackDelay = 0;
		int32_t attackBeatFrame = 0;
		int32_t attackFxGroupID = 0;
		int32_t attackSoundFileID = 0;
		int32_t skill1Type = 0;
		int32_t skill1Percent = 0;
		int32_t skill1Range = 0;
		int32_t skill1CoolTime = 0;
		int32_t skill1LV = 0;
		int32_t skill1AniPartID = 0;
		int32_t skill1EndFrame = 0;
		int32_t skill1Delay = 0;
		int32_t skill1BeatFrame = 0;
		int32_t skill1AbilityID = 0;
		int32_t skill2Type = 0;
		int32_t skill2Percent = 0;
		int32_t skill2Range = 0;
		int32_t skill2CoolTime = 0;
		int32_t skill2LV = 0;
		int32_t skill2AniPartID = 0;
		int32_t skill2EndFrame = 0;
		int32_t skill2Delay = 0;
		int32_t skill2BeatFrame = 0;
		int32_t skill2AbilityID = 0;
		int32_t skill3Type = 0;
		int32_t skill3Percent = 0;
		int32_t skill3Range = 0;
		int32_t skill3CoolTime = 0;
		int32_t skill3LV = 0;
		int32_t skill3AniPartID = 0;
		int32_t skill3EndFrame = 0;
		int32_t skill3Delay = 0;
		int32_t skill3BeatFrame = 0;
		int32_t skill3AbilityID = 0;
		int32_t passive1Percent = 0;
		int32_t passive1LV = 0;
		int32_t passive1AddExp = 0;
		int32_t passive1ID = 0;
		int32_t passive1ExtraMoney = 0;
		int32_t passive2Percent = 0;
		int32_t passive2LV = 0;
		int32_t passive2AddExp = 0;
		int32_t passive2ID = 0;
		int32_t passive2ExtraMoney = 0;
		int32_t passive3Percent = 0;
		int32_t passive3LV = 0;
		int32_t passive3AddExp = 0;
		int32_t passive3ID = 0;
		int32_t passive3ExtraMoney = 0;
	};

	class MonsterAttackTable : public GameDataTable
	{
	public:
		 static constexpr int64_t INDEX = 54;

	public:
		void LoadFromFile(const std::filesystem::path& path);

		auto Find(int32_t index) const -> const MonsterAttack*;
		auto Get() const -> const std::vector<MonsterAttack>&;

	private:
		std::vector<MonsterAttack> _vector;
		std::unordered_map<int32_t, const MonsterAttack*> _umap;
	};
}

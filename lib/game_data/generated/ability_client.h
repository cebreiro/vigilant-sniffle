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
	struct AbilityClient
	{
		AbilityClient() = default;
		explicit AbilityClient(StreamReader& reader);

		int32_t index = 0;
		std::string abilityName;
		int32_t abilityRoutine = 0;
		int32_t totalTime = 0;
		int32_t _1Hand00Pid = 0;
		int32_t _2Hand00Pid = 0;
		int32_t spearPid = 0;
		int32_t polearmPid = 0;
		int32_t glovePid = 0;
		int32_t bowPid = 0;
		int32_t handgunPid = 0;
		int32_t doublegunPid = 0;
		int32_t shotgunPid = 0;
		int32_t throwPid = 0;
		int32_t _1Hand00StartDamageFrame = 0;
		int32_t _2Hand00StartDamageFrame = 0;
		int32_t spearStartDamageFrame = 0;
		int32_t polearmDamageFrame = 0;
		int32_t gloveStartDamageFrame = 0;
		int32_t bowStartDamageFrame = 0;
		int32_t handgunStartDamageFrame = 0;
		int32_t doublegunStartDamageFrame = 0;
		int32_t shotgunStartDamageFrame = 0;
		int32_t throwStartDamageFrame = 0;
		int32_t _1Hand00Timing = 0;
		int32_t _2Hand00Timing = 0;
		int32_t spearTiming = 0;
		int32_t polearmTiming = 0;
		int32_t gloveTiming = 0;
		int32_t bowTiming = 0;
		int32_t handgunTiming = 0;
		int32_t doublegunTiming = 0;
		int32_t shotgunTiming = 0;
		int32_t throwTiming = 0;
		int32_t _1Hand00FullTime = 0;
		int32_t _2Hand00FullTime = 0;
		int32_t spearFullTime = 0;
		int32_t polearmFullTime = 0;
		int32_t gloveFullTime = 0;
		int32_t bowFullTime = 0;
		int32_t handgunFullTime = 0;
		int32_t doublegunFullTime = 0;
		int32_t shotgunFullTime = 0;
		int32_t throwFullTime = 0;
		int32_t isUniqueItemAbility = 0;
		int32_t uniqueItemAbilityPid = 0;
		int32_t chargeFXGid = 0;
		int32_t chargeFXPid = 0;
		int32_t defaultShockFX = 0;
		int32_t shockFXGid = 0;
		int32_t shockFXPid = 0;
		int32_t abilityDelay = 0;
		int32_t locationTab = 0;
		int32_t locationX = 0;
		int32_t locationY = 0;
		std::string detail;
		int32_t iconTextureId = 0;
		int32_t iconLocation = 0;
		int32_t iconTexture2Id = 0;
		int32_t iconLocation2 = 0;
		int32_t reserved1 = 0;
		int32_t reserved2 = 0;
		float dmgPenalty = 0.f;
		int32_t category = 0;
		int32_t cancelable = 0;
		int32_t five = 0;
		int32_t spendSP = 0;
		int32_t length = 0;
		int32_t keepTime = 0;
		int32_t damageLength = 0;
		int32_t usage = 0;
		int32_t applyTarget = 0;
		int32_t addWeaponRange = 0;
		int32_t damageStyle = 0;
		int32_t damageReserved1 = 0;
		int32_t damageReserved2 = 0;
		int32_t damageMotionType = 0;
		int32_t sideEffect1 = 0;
		int32_t sideEffect2 = 0;
		int32_t statusValType1 = 0;
		int32_t statusValType2 = 0;
		int32_t statusProb = 0;
		int32_t statusReserved11 = 0;
		int32_t statusReserved12 = 0;
		int32_t statusReserved21 = 0;
		int32_t statusReserved22 = 0;
		int32_t job = 0;
		int32_t exp = 0;
		float speed = 0.f;
		int32_t requireItem = 0;
		int32_t spendItem = 0;
		int32_t spendBullet = 0;
		int32_t increaseHit = 0;
		int32_t needWeapon = 0;
	};

	class AbilityClientTable : public GameDataTable
	{
	public:
		 static constexpr int64_t INDEX = 1;

	public:
		void LoadFromFile(const std::filesystem::path& path);

		auto Find(int32_t index) const -> const AbilityClient*;
		auto Get() const -> const std::vector<AbilityClient>&;

	private:
		std::vector<AbilityClient> _vector;
		std::unordered_map<int32_t, const AbilityClient*> _umap;
	};
}

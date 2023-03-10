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
	struct WeaponMotionType
	{
		WeaponMotionType() = default;
		explicit WeaponMotionType(StreamReader& reader);

		int32_t index = 0;
		int32_t _default = 0;
		float defaultSpeed = 0.f;
		int32_t walk = 0;
		float walkSpeed = 0.f;
		int32_t run = 0;
		float runSpeed = 0.f;
		int32_t idle = 0;
		float idleSpeed = 0.f;
		int32_t disArm = 0;
		float disArmSpeed = 0.f;
		int32_t reArm = 0;
		float reArmSpeed = 0.f;
		int32_t reLoad = 0;
		float reLoadSpeed = 0.f;
		int32_t maxCombo = 0;
		int32_t attackMotion1 = 0;
		float attackMotion1Speed = 0.f;
		int32_t attackMotion2 = 0;
		float attackMotion2Speed = 0.f;
		int32_t attackMotion3 = 0;
		float attackMotion3Speed = 0.f;
		int32_t attackMotion4 = 0;
		float attackMotion4Speed = 0.f;
		int32_t attackMotion5 = 0;
		float attackMotion5Speed = 0.f;
		int32_t attackMotion6 = 0;
		float attackMotion6Speed = 0.f;
		int32_t attackMotion7 = 0;
		float attackMotion7Speed = 0.f;
		int32_t attackMotion8 = 0;
		float attackMotion8Speed = 0.f;
		int32_t attackMotion9 = 0;
		float attackMotion9Speed = 0.f;
		int32_t attackMotion10 = 0;
		float attackMotion10Speed = 0.f;
		int32_t feedbackMotion1 = 0;
		float feedbackMotion1Speed = 0.f;
		int32_t feedbackMotion2 = 0;
		float feedbackMotion2Speed = 0.f;
		int32_t feedbackMotion3 = 0;
		float feedbackMotion3Speed = 0.f;
		int32_t feedbackMotion4 = 0;
		float feedbackMotion4Speed = 0.f;
		int32_t feedbackMotion5 = 0;
		float feedbackMotion5Speed = 0.f;
		int32_t feedbackMotion6 = 0;
		float feedbackMotion6Speed = 0.f;
		int32_t feedbackMotion7 = 0;
		float feedbackMotion7Speed = 0.f;
		int32_t feedbackMotion8 = 0;
		float feedbackMotion8Speed = 0.f;
		int32_t feedbackMotion9 = 0;
		float feedbackMotion9Speed = 0.f;
		int32_t feedbackMotion10 = 0;
		float feedbackMotion10Speed = 0.f;
	};

	class WeaponMotionTypeTable : public GameDataTable
	{
	public:
		 static constexpr int64_t INDEX = 83;

	public:
		void LoadFromFile(const std::filesystem::path& path);

		auto Find(int32_t index) const -> const WeaponMotionType*;
		auto Get() const -> const std::vector<WeaponMotionType>&;

	private:
		std::vector<WeaponMotionType> _vector;
		std::unordered_map<int32_t, const WeaponMotionType*> _umap;
	};
}

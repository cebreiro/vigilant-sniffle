#pragma once
#include "lib/game_base/type/job.h"

namespace cebreiro::gamedata
{
	struct JobReference;
}

namespace cebreiro::zone
{
	class PlayerJob
	{
	public:
		PlayerJob() = default;
		PlayerJob(const gamedata::JobReference* data, type::Job type, int32_t level, int32_t exp, int32_t point);

		bool CanPromote(type::Job type) const;

		void SetLevel(int32_t level);
		void SetEXP(int32_t exp);
		void SetPoint(int32_t point);

		auto GetLevel() const -> int32_t;
		auto GetEXP() const -> int32_t;
		auto GetPoint() const -> int32_t;

		auto Type() const -> type::Job;
		auto MaxLevel() const -> int32_t;
		auto MaxHPFactor() const -> double;
		auto MaxSPFactor() const -> double;
		auto HitRateFactor() const -> double;
		auto DefenseFactor() const -> double;
		auto HPRecoveryFactor() const -> double;
		auto SPRecoveryFactor() const -> double;
		auto SpeedFactor() const -> double;

	private:
		const gamedata::JobReference* _data = nullptr;
		type::Job _type = type::Job::Any;
		int32_t _level = 0;
		int32_t _exp = 0;
		int32_t _point = 0;
	};
}
#include "player_job.h"

#include "lib/game_data/generated/job_reference.h"
#include "lib/game_data/utility/job.h"

namespace cebreiro::zone
{
	PlayerJob::PlayerJob(const gamedata::JobReference* data, type::Job type, int32_t level, int32_t exp, int32_t point)
		: _data(data)
		, _type(type)
		, _level(level)
		, _exp(exp)
		, _point(point)
	{
		assert(_data);
	}

	bool PlayerJob::CanPromote(type::Job type) const
	{
		if (GetLevel() < MaxLevel())
		{
			return false;
		}

		if (!gamedata::IsPromotionJobFromNovice(Type(), type))
		{
			return false;
		}

		return true;
	}

	void PlayerJob::SetLevel(int32_t level)
	{
		_level = level;
	}

	void PlayerJob::SetEXP(int32_t exp)
	{
		_exp = exp;
	}

	void PlayerJob::SetPoint(int32_t point)
	{
		_point = point;
	}

	auto PlayerJob::GetLevel() const -> int32_t
	{
		return _level;
	}

	auto PlayerJob::GetEXP() const -> int32_t
	{
		return _exp;
	}

	auto PlayerJob::GetPoint() const -> int32_t
	{
		return _point;
	}

	auto PlayerJob::Type() const -> type::Job
	{
		return _type;
	}

	auto PlayerJob::MaxLevel() const -> int32_t
	{
		assert(_data);
		return _data->maxJobLevel;
	}

	auto PlayerJob::MaxHPFactor() const -> double
	{
		assert(_data);
		return _data->mHPFactor;
	}

	auto PlayerJob::MaxSPFactor() const -> double
	{
		assert(_data);
		return _data->mSPFactor;
	}

	auto PlayerJob::HitRateFactor() const -> double
	{
		assert(_data);
		return _data->pHRatFactor;
	}

	auto PlayerJob::DefenseFactor() const -> double
	{
		assert(_data);
		return _data->defenseFactor;
	}

	auto PlayerJob::HPRecoveryFactor() const -> double
	{
		assert(_data);
		return _data->hPRecoveryFactor;
	}

	auto PlayerJob::SPRecoveryFactor() const -> double
	{
		assert(_data);
		return _data->sPRecoveryFactor;
	}

	auto PlayerJob::SpeedFactor() const -> double
	{
		assert(_data);
		return _data->avatarSpeedFactor;
	}
}

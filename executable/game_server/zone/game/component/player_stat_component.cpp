#include "player_stat_component.h"

#include "lib/game_base/db/character.h"
#include "zone/game/object/game_object.h"
#include "zone/game/component/player_job_component.h"
#include "zone/game/domain/job/player_job.h"

namespace cebreiro::zone
{
	PlayerStatComponent::PlayerStatComponent(GameObject& object, const gamebase::CharacterStat& stat)
		: ComponentBase(object)
		, _hp(stat.hp)
		, _sp(stat.mp)
		, _statPoint(stat.stat_point)
	{
		auto list = std::initializer_list<std::pair<type::Stat, PlayerStat>>{
			{ type::Stat::Gender, PlayerStat(stat.gender) },
			{ type::Stat::Str, PlayerStat(stat.str) },
			{ type::Stat::Dex, PlayerStat(stat.dex) },
			{ type::Stat::Accr, PlayerStat(stat.accr) },
			{ type::Stat::Health, PlayerStat(stat.health) },
			{ type::Stat::Intell, PlayerStat(stat.intell) },
			{ type::Stat::Wisdom, PlayerStat(stat.wis) },
			{ type::Stat::Will, PlayerStat(stat.will) },
			{ type::Stat::Water, PlayerStat(stat.water) },
			{ type::Stat::Fire, PlayerStat(stat.fire) },
			{ type::Stat::Lightning, PlayerStat(stat.lightning) },
		};

		_statContainer.insert(list);
	}

	void PlayerStatComponent::OnTick(time_point_t now)
	{
		if (!_regen)
		{
			return;
		}

		auto duration = std::chrono::seconds(1);

		if (now - _lastRegenTimePoint < duration)
		{
			return;
		}

		// client 48C620h
		double hp = GetStat(type::Stat::HP);
		double sp = GetStat(type::Stat::SP);
		double maxHP = GetStat(type::Stat::MaxHP);
		double maxSP = GetStat(type::Stat::MaxSP);

		if (hp < maxHP)
		{
			double recoveryHP = GetStat(type::Stat::RecoveryRateHP) * 0.2;
			SetStat(type::Stat::HP, std::min(hp + recoveryHP, maxHP));
		}

		if (sp < maxSP)
		{
			double recoverySP = GetStat(type::Stat::RecoveryRateSP) * 0.25;
			SetStat(type::Stat::SP, std::min(sp + recoverySP, maxSP));
		}

		_lastRegenTimePoint += duration;
	}

	void PlayerStatComponent::StartRegen()
	{
		_regen = true;
		_lastRegenTimePoint = clock_t::now();
	}

	void PlayerStatComponent::StopRegen()
	{
		_regen = false;
	}

	void PlayerStatComponent::UpdateStats()
	{
		for (type::Stat type : _statContainer | srv::keys)
		{
			switch (type)
			{
			case type::Stat::HP:
			case type::Stat::SP:
				break;
			case type::Stat::MaxHP:
				UpdateMaxHP();
				break;
			case type::Stat::RecoveryRateHP:
				UpdateRecoveryRateHP();
				break;
			case type::Stat::MaxSP:
				UpdateMaxSP();
				break;
			case type::Stat::RecoveryRateSP:
				UpdateRecoveryRateSP();
				break;
			case type::Stat::PhysicalDefense:
				UpdatePhysicalDefense();
				break;
			case type::Stat::Hit:
				UpdateHit();
				break;
			default:
				SetStat(type, CalculateStatSum(type));
			}
		}
	}

	auto PlayerStatComponent::GetStat(type::Stat type) const -> double
	{
		if (type == type::Stat::HP)
		{
			return _hp;
		}
		else if (type == type::Stat::SP)
		{
			return _sp;
		}
		else
		{
			auto iter = _stats.find(type);
			return iter != _stats.end() ? iter->second : 0;
		}
	}

	void PlayerStatComponent::UpdateMaxHP()
	{
		const PlayerJobComponent& jobComponent = _object.Get<PlayerJobComponent>();
		int32_t jobLevel = CalculateJobLevel(jobComponent);
		double factor = jobComponent.GetMainJob().MaxHPFactor();

		// client 487500h
		double value = (4.0 * (GetStat(type::Stat::Health) + 2.0 * jobLevel) * factor) + 10.0;
		value += CalculateStatSum(type::Stat::MaxHP);

		SetStat(type::Stat::MaxHP, value);

		if (GetStat(type::Stat::HP) > value)
		{
			SetStat(type::Stat::HP, value);
		}
	}

	void PlayerStatComponent::UpdateRecoveryRateHP()
	{
		const PlayerJobComponent& jobComponent = _object.Get<PlayerJobComponent>();
		double factor = jobComponent.GetMainJob().HPRecoveryFactor();

		// client 4875C0h
		double value = factor * GetStat(type::Stat::Health) * 0.2 + 2.0;
		value += CalculateStatSum(type::Stat::RecoveryRateHP);

		SetStat(type::Stat::RecoveryRateHP, value);
	}

	void PlayerStatComponent::UpdateMaxSP()
	{
		const PlayerJobComponent& jobComponent = _object.Get<PlayerJobComponent>();
		int32_t jobLevel = CalculateJobLevel(jobComponent);
		double factor = jobComponent.GetMainJob().MaxSPFactor();

		double intell = GetStat(type::Stat::Intell);
		double wisdom = GetStat(type::Stat::Wisdom);
		double will = GetStat(type::Stat::Will);

		// client 487610h
		double value = (2.0 * (intell + wisdom + will + 5.0 * jobLevel)) * factor;
		value += CalculateStatSum(type::Stat::MaxSP);

		SetStat(type::Stat::MaxSP, value);

		if (GetStat(type::Stat::SP) > value)
		{
			SetStat(type::Stat::SP, value);
		}
	}

	void PlayerStatComponent::UpdateRecoveryRateSP()
	{
		const PlayerJobComponent& jobComponent = _object.Get<PlayerJobComponent>();
		double factor = jobComponent.GetMainJob().SPRecoveryFactor();

		// client 487700h
		double value = factor * GetStat(type::Stat::Will) * 0.15 + 2.0;
		value += CalculateStatSum(type::Stat::RecoveryRateSP);

		SetStat(type::Stat::RecoveryRateSP, value);
	}

	void PlayerStatComponent::UpdatePhysicalDefense()
	{
		const PlayerJobComponent& jobComponent = _object.Get<PlayerJobComponent>();
		int32_t jobLevel = CalculateJobLevel(jobComponent);
		double factor = jobComponent.GetMainJob().DefenseFactor();

		// client 4877A0h
		double value = (2.0 * GetStat(type::Stat::Dex)) + jobLevel * factor + 10.0;
		value += CalculateStatSum(type::Stat::PhysicalDefense);

		SetStat(type::Stat::PhysicalDefense, value);
	}

	void PlayerStatComponent::UpdateHit()
	{
		const PlayerJobComponent& jobComponent = _object.Get<PlayerJobComponent>();
		int32_t jobLevel = CalculateJobLevel(jobComponent);
		double factor = jobComponent.GetMainJob().HitRateFactor();

		// client 487820h
		double value = (2.0 * GetStat(type::Stat::Accr)) + (jobLevel) *factor + 10.0;
		value += CalculateStatSum(type::Stat::Hit);

		SetStat(type::Stat::Hit, value);
	}

	void PlayerStatComponent::SetStat(type::Stat type, double value)
	{
		if (type == type::Stat::HP)
		{
			_hp = value;
		}
		else if (type == type::Stat::SP)
		{
			_sp = value;
		}
		else
		{
			_stats[type] = value;
		}
	}

	auto PlayerStatComponent::CalculateStatSum(type::Stat type) const -> double
	{
		switch (type)
		{
		case type::Stat::Gender:
		case type::Stat::CharLv:
		case type::Stat::HP:
		case type::Stat::SP:
		{
			assert(_statContainer.contains(type));
			return _statContainer.at(type).base;
		}
		}

		auto calculateSum = [this](type::Stat type) -> double
		{
			auto iter = _statContainer.find(type);
			if (iter == _statContainer.end())
			{
				return 0;
			}

			const PlayerStat& stat = iter->second;

			double sum = 0;
			sum += stat.base;
			sum += stat.item;

			return sum;
		};

		auto calculateStatBonus = [calculateSum](type::Stat type) -> double
		{
			switch (type)
			{
			case type::Stat::Str:
			case type::Stat::Dex:
			case type::Stat::Accr:
			case type::Stat::Health:
			case type::Stat::Intell:
			case type::Stat::Wisdom:
			case type::Stat::Will:
				return calculateSum(type::Stat::AllBaseStat);
			case type::Stat::Fire:
			case type::Stat::Water:
			case type::Stat::Lightning:
				return calculateSum(type::Stat::AllElemental);
			default:
				return 0;
			}
		};

		return calculateSum(type) + calculateStatBonus(type);
	}

	auto PlayerStatComponent::CalculateJobLevel(const PlayerJobComponent& jobComponent) -> int32_t
	{
		int32_t sum = jobComponent.GetNoviceJob().GetLevel();

		const PlayerJob* job = jobComponent.GetAdvancedJob();
		if (job)
		{
			sum += job->GetLevel() - 1;
		}

		return sum;
	}
}

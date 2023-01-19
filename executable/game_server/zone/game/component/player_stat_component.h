#pragma once
#include "lib/game_base/type/stat.h"
#include "zone/game/component/component_base.h"
#include "zone/game/domain/stat/player_stat.h"

namespace cebreiro::gamebase
{
	struct CharacterStat;
}

namespace cebreiro::zone
{
	class PlayerJobComponent;
}

namespace cebreiro::zone
{
	class PlayerStatComponent : public ComponentBase
	{
	public:
		PlayerStatComponent(GameObject& object, const gamebase::CharacterStat& stat);

		void OnTick(time_point_t now) override;

		void StartRegen();
		void StopRegen();
		void UpdateStats();

		auto GetStat(type::Stat type) const -> double;

		template <std::integral T>
		auto GetStatT(type::Stat type) const -> T;

	private:
		void UpdateMaxHP();
		void UpdateRecoveryRateHP();
		void UpdateMaxSP();
		void UpdateRecoveryRateSP();
		void UpdatePhysicalDefense();
		void UpdateHit();

		void SetStat(type::Stat type, double value);

		auto CalculateStatSum(type::Stat type) const -> double;

	private:
		static auto CalculateJobLevel(const PlayerJobComponent& jobComponent) -> int32_t;

	private:
		bool _regen = false;
		time_point_t _lastRegenTimePoint;
		double _hp = 0;
		double _sp = 0;
		int32_t _exp = 0;
		int32_t _statPoint = 0;
		boost::container::flat_map<type::Stat, PlayerStat> _statContainer;
		boost::container::flat_map<type::Stat, double>  _stats;
	};

	template <std::integral T>
	auto PlayerStatComponent::GetStatT(type::Stat type) const -> T
	{
		return static_cast<T>(GetStat(type));
	}
}

#pragma once
#include "lib/game_base/type/job.h"
#include "zone/game/component/component_base.h"

namespace cebreiro::gamebase
{
	struct CharacterJob;
}

namespace cebreiro::gamedata
{
	class JobReferenceTable;
}

namespace cebreiro::zone
{
	class PlayerJob;
}

namespace cebreiro::zone
{
	class PlayerJobComponent : public ComponentBase
	{
	public:
		PlayerJobComponent(GameObject& object, const gamebase::CharacterJob& characterJob);
		~PlayerJobComponent();

		bool Promote(type::Job type);

		void AddEXP(int32_t value);

		auto GetMainJob() const -> const PlayerJob&;
		auto GetNoviceJob() const -> const PlayerJob&;
		auto GetAdvancedJob() const -> const PlayerJob*;
		
	private:
		auto FindJob(int32_t id) -> PlayerJob*;

	private:
		std::shared_ptr<gamedata::JobReferenceTable> _data;
		std::array<std::unique_ptr<PlayerJob>, 4> _jobs = {};
		PlayerJob* _mainJob = nullptr;
	};
}
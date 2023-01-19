#include "player_job_component.h"

#include "lib/game_base/db/character.h"
#include "lib/game_base/type/job.h"
#include "lib/game_data/game_data_source.h"
#include "lib/game_data/generated/job_reference.h"
#include "zone/game/domain/job/player_job.h"
#include "zone/game/object/game_object.h"

namespace cebreiro::zone
{
	PlayerJobComponent::PlayerJobComponent(GameObject& object, const gamebase::CharacterJob& characterJob)
		: ComponentBase(object)
		, _data(_object.GetDataSource().Get<gamedata::JobReferenceTable>())
	{
		SetDoTick(false);

		auto list = std::array{
			std::tuple{characterJob.job1, characterJob.job1_level, characterJob.job1_exp, characterJob.job1_sp},
			std::tuple{characterJob.job2, characterJob.job2_level, characterJob.job2_exp, characterJob.job2_sp},
			std::tuple{characterJob.job3, characterJob.job3_level, characterJob.job3_exp, characterJob.job3_sp},
			std::tuple{characterJob.job_sub, characterJob.job_sub_level, characterJob.job_sub_exp, characterJob.job_sub_sp},
		};
		static_assert(std::extent_v<decltype(_jobs)> == std::extent_v<decltype(list)>);

		for (size_t i = 0; i < list.max_size(); ++i)
		{
			auto [job, level, exp, point] = list[i];
			auto type = static_cast<type::Job>(job);

			if (!IsValid(type))
			{
				continue;
			}

			const gamedata::JobReference* data = _data->Find(job);
			if (!data)
			{
				continue;
			}

			_jobs[i] = std::make_unique<PlayerJob>(data, type, level, exp, point);
		}

		if (!_jobs[0])
		{
			throw StacktraceException("invalid data");
		}

		if (_jobs[1])
		{
			_mainJob = _jobs[1].get();
		}
		else
		{
			_mainJob = _jobs[0].get();
		}
	}

	PlayerJobComponent::~PlayerJobComponent()
	{
	}

	bool PlayerJobComponent::Promote(type::Job type)
	{
		std::unique_ptr<PlayerJob>& advancedJob = _jobs[1];

		if (advancedJob)
		{
			return false;
		}

		const PlayerJob& noviceJob = GetNoviceJob();
		if (!noviceJob.CanPromote(type))
		{
			return false;
		}

		const gamedata::JobReference* data = _data->Find(static_cast<int32_t>(type));
		if (!data)
		{
			return false;
		}

		advancedJob = std::make_unique<PlayerJob>(data, type, 1, 0, 0);

		// TODO: send to controller

		return true;
	}

	void PlayerJobComponent::AddEXP(int32_t value)
	{
		(void)value;

		// TODO: implement here
	}

	auto PlayerJobComponent::GetMainJob() const -> const PlayerJob&
	{
		const PlayerJob* job = GetAdvancedJob();
		if (job)
		{
			return *job;
		}

		return GetNoviceJob();
	}

	auto PlayerJobComponent::GetNoviceJob() const -> const PlayerJob&
	{
		assert(_jobs[0]);
		return *_jobs[0];
	}

	auto PlayerJobComponent::GetAdvancedJob() const -> const PlayerJob*
	{
		return _jobs[1].get();
	}

	auto PlayerJobComponent::FindJob(int32_t id) -> PlayerJob*
	{
		auto iter = sr::find_if(_jobs, [id](const std::unique_ptr<PlayerJob>& job)
			{
				return job->Type() == static_cast<type::Job>(id);
			});
		return iter != _jobs.end() ? iter->get() : nullptr;
	}
}

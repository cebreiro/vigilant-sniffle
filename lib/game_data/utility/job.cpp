#include "job.h"

namespace cebreiro::gamedata
{
	bool IsPromotionJobFromNovice(type::Job first, type::Job second)
	{
		switch (first)
		{
		case type::Job::NoviceFighter:
		{
			switch (second)
			{
			case type::Job::SwordWarrior:
			case type::Job::Berserker:
			case type::Job::Dragoon:
			case type::Job::MartialArtist:
				return true;
			}
		}
		case type::Job::NoviceRanger:
		{
			switch (second)
			{
			case type::Job::Archer:
			case type::Job::Gunner:
			case type::Job::Agent:
			case type::Job::TreasureHunter:
				return true;
			}
		}
		case type::Job::NoviceMagician:
		{
			switch (second)
			{
			case type::Job::Mage:
			case type::Job::Healer:
			case type::Job::Mystic:
			case type::Job::Engineer:
				return true;
			}
		}
		case type::Job::NoviceArtisan:
		{
			switch (second)
			{
			case type::Job::WeaponSmith:
			case type::Job::Designer:
			case type::Job::Cook:
			case type::Job::Chemist:
				return true;
			}
		}
		}

		return false;
	}
}
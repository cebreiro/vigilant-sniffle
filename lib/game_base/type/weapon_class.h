#pragma once
#include <cstdint>
#include "lib/common/enum_class.h"

namespace cebreiro::type
{
	ENUM_CLASS(WeaponClass, int32_t,
		(None, -1)
		(OneHandedSword, 100)
		(TwoHandedSword, 200)
		(BigSword, 300)
		(Hammer, 400)
		(Axe, 500)
		(Spear, 600)
		(Polearm, 700)
		(Knuckle, 800)
		(Shuriken, 900)
		(Pistol, 1000)
		(DoublePistol, 1100)
		(Shotgun, 1200)
		(Machinegun, 1300)
		(Bow, 1400)
		(Crossbow, 1500)
		(Dagger, 1600)
		(Wand, 1700)
		(Bellows, 7000)
		(Iron, 7100)
		(Griddle, 7200)
		(Drill, 7300)
	)
}
#pragma once
#include <cstdint>
#include "lib/common/enum_class.h"

namespace cebreiro::type
{
	// sox table 13000000 + jobId
	ENUM_CLASS(Job, int32_t,
		(Any, 900) /* 모든 직업 mix skill*/
		(NoviceFighter, 1100) /* 초보전사 */
		(NoviceRanger, 1201) /* 초보레인저 */
		(NoviceMagician, 1302) /* 초보매지션 */
		(NoviceArtisan, 1403) /* 초보조합사 */
		(SwordWarrior, 2100) /* 검투사 */
		(Berserker, 2101) /* 광전사 */
		(Dragoon, 2102) /* 창기사 */
		(MartialArtist, 2103) /* 권법가 */
		(Archer, 2208) /* 아처 */
		(Gunner, 2209) /* 건너 */
		(Agent, 2210) /* 에이전트 */
		(TreasureHunter, 2211) /* 트레저 헌터 */
		(Mage, 2304) /* 메이지 */
		(Healer, 2305) /* 힐러 */
		(Mystic, 2306) /* 미스틱 */
		(Engineer, 2307) /* 엔지니어 */
		(WeaponSmith, 2412) /* 대장장이 */
		(Designer, 2413) /* 디자이너 */
		(Cook, 2414) /* 요리사 */
		(Chemist, 2415) /* 세공사 */
	)
}
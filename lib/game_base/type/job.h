#pragma once
#include <cstdint>
#include "lib/common/enum_class.h"

namespace cebreiro::type
{
	// sox table 13000000 + jobId
	ENUM_CLASS(Job, int32_t,
		(Any, 900) /* ��� ���� mix skill*/
		(NoviceFighter, 1100) /* �ʺ����� */
		(NoviceRanger, 1201) /* �ʺ������� */
		(NoviceMagician, 1302) /* �ʺ������� */
		(NoviceArtisan, 1403) /* �ʺ����ջ� */
		(SwordWarrior, 2100) /* ������ */
		(Berserker, 2101) /* ������ */
		(Dragoon, 2102) /* â��� */
		(MartialArtist, 2103) /* �ǹ��� */
		(Archer, 2208) /* ��ó */
		(Gunner, 2209) /* �ǳ� */
		(Agent, 2210) /* ������Ʈ */
		(TreasureHunter, 2211) /* Ʈ���� ���� */
		(Mage, 2304) /* ������ */
		(Healer, 2305) /* ���� */
		(Mystic, 2306) /* �̽�ƽ */
		(Engineer, 2307) /* �����Ͼ� */
		(WeaponSmith, 2412) /* �������� */
		(Designer, 2413) /* �����̳� */
		(Cook, 2414) /* �丮�� */
		(Chemist, 2415) /* ������ */
	)
}
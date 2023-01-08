#pragma once
#include <cstdint>
#include "lib/common/enum_class.h"

namespace cebreiro::type
{
/*
 * 2 케릭터 레벨
 * 5 힘
 * 6 민첩
 * 7 정확
 * 8 건강
 * 9 지능
 * 10 지식
 * 11 의지
 * 12 표시x
 * 13 불 속성
 * 14 물 속성
 * 15 번개 속성
 * 16 최대 HP
 * 17 HP 회복률
 * 18 최대 SP
 * 19 SP 회복률
 * 20 이동속도
 * 21 분노게이지 차는 속도
 * 22 분노게이지 주는 속도
 * 23 공격속도 - 1005 가 게임에선 5%로 표기
 * 24 공격 딜레이 감소
 * 25
 * 26
 * 27 힘에 의한 물리 공격
 * 28 민첩에 의한 물리공격
 * 29 방어(물리 방어)
 * 30 명중
 * 31 회피 - 1015 -> 15%
 * 32 크리 - 1015 -> 15%
 * 100 모든 원소 속성
 * 101 5~11 모든 스텟 상승
 */
	ENUM_CLASS(Stat, int32_t,
		(None, 0)
		(Gender, 1)
		(CharLv, 2)
		(HP, 3)
		(SP, 4)
		(Str, 5)
		(Dex, 6)
		(Accr, 7)
		(Health, 8)
		(Intell, 9)
		(Wisdom, 10)
		(Will, 11)
		(Unk12, 12)
		(Fire, 13)
		(Water, 14)
		(Lightning, 15)
		(MaxHP, 16)
		(RecoveryRateHP, 17)
		(MaxSP, 18)
		(RecoveryRateSP, 19)
		(Speed, 20)
		(RageUpSpeed, 21)
		(RageDownSpeed, 22)
		(AttackSpeed, 23)
		(AttackDelayDecrease, 24)
		(Unk25, 25)
		(Unk26, 26)
		(PhysicalAttackStr, 27)
		(PhysicalAttackDex, 28)
		(PhysicalDefense, 29) // 스탯 창에 방어
		(Hit, 30) // 스탯 창에 명중
		(Miss, 31)
		(Critical, 32)
		(Protection, 45) // 스탯 창에 보호
		(Resistance, 46) // 마법 시전 중 취소 확률 저하(매지션 강화 스킬 effect)
		(AttackRange, 47) // 원거리 사정거리

		(AttackReflection, 60)
		(AllElemental, 100)
		(AllBaseStat, 101)
		(BaseAttack, 102)
		(RecoveryHPContinue, 2000)
	)

	ENUM_CLASS(MonsterStatType, int32_t,
		(HitRate, 2) // client 4B4B40h
		(PhysicalDefense, 3) // client 4B4B90h
		(Str, 4)
		(Dex, 5)
		(Accr, 6)
		(Health, 7)
		(Intell, 8)
		(Wisdom, 9)
		(Will, 10)
		(Fire, 11) // client 4B4A40h
		(Water, 12) // client 4B4A40h
		(Lightning, 13) // client 4B4A40h
	)
}
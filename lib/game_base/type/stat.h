#pragma once
#include <cstdint>
#include "lib/common/enum_class.h"

namespace cebreiro::type
{
/*
 * 2 �ɸ��� ����
 * 5 ��
 * 6 ��ø
 * 7 ��Ȯ
 * 8 �ǰ�
 * 9 ����
 * 10 ����
 * 11 ����
 * 12 ǥ��x
 * 13 �� �Ӽ�
 * 14 �� �Ӽ�
 * 15 ���� �Ӽ�
 * 16 �ִ� HP
 * 17 HP ȸ����
 * 18 �ִ� SP
 * 19 SP ȸ����
 * 20 �̵��ӵ�
 * 21 �г������ ���� �ӵ�
 * 22 �г������ �ִ� �ӵ�
 * 23 ���ݼӵ� - 1005 �� ���ӿ��� 5%�� ǥ��
 * 24 ���� ������ ����
 * 25
 * 26
 * 27 ���� ���� ���� ����
 * 28 ��ø�� ���� ��������
 * 29 ���(���� ���)
 * 30 ����
 * 31 ȸ�� - 1015 -> 15%
 * 32 ũ�� - 1015 -> 15%
 * 100 ��� ���� �Ӽ�
 * 101 5~11 ��� ���� ���
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
		(PhysicalDefense, 29) // ���� â�� ���
		(Hit, 30) // ���� â�� ����
		(Miss, 31)
		(Critical, 32)
		(Protection, 45) // ���� â�� ��ȣ
		(Resistance, 46) // ���� ���� �� ��� Ȯ�� ����(������ ��ȭ ��ų effect)
		(AttackRange, 47) // ���Ÿ� �����Ÿ�

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
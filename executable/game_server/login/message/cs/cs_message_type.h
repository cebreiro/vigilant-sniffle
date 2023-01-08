#pragma once
#include "lib/common/enum_class.h"

namespace cebreiro::login
{
	ENUM_CLASS(CSMessageType, int8_t,
		(LoginRequest, 0i8)
		(BackToLoginServer, 1i8)
		(WorldSelectRequest, 2i8)
		(LogoutRequest, 3i8) // gateway ���� ����, zone���� '���� ����' ���� �� ��, login�� reconnect �Ͽ� ����
		(UnknownOpcode04, 4i8)
		(UnknownOpcode05, 5i8)
		(ReloginRequest, 6i8)
		(UnknownOpcode07, 7i8)
	)
}
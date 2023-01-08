#pragma once
#include "lib/common/enum_class.h"

namespace cebreiro::login
{
	ENUM_CLASS(SCMessageType, int8_t,
		(Hello, 0)
		(LoginFailResponse, 1)
		(WorldListNotify, 4)
		(WorldSelectResponse, 7)
	)
}
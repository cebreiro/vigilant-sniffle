#pragma once
#include "lib/common/enum_class.h"

namespace cebreiro::gateway
{
	// search
	// push : 68
	// value: XX 70 00 00 (example)
	ENUM_CLASS(CSMessageType, int32_t,
		(ClientVersionRequest, 0x7000i32) // sub_5961B0
		(AuthenticationRequest, 0x7002i32) // sub_596230
		(CharacterListRequest, 0x7004i32)
		(CharacterSelectRequest, 0x7005i32)
		(CharacterCreateRequest, 0x7007i32)
		(CharacterDeleteRequest, 0x7008i32)
		(CharacterNameCheckRequest, 0x700Ai32)
		(UnknownOpcode0x7040, 0x7040i32) // sub_596320
	)
}
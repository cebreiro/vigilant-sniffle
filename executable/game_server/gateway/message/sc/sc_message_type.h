#pragma once
#include "lib/common/enum_class.h"

namespace cebreiro::gateway
{
	// address 0x00595F40
	ENUM_CLASS(SCMessageType, int32_t,
		(ClientVersionResponse, 0x8000)
		(AuthenticationResponse, 0x8002)
		(CharacterListResponse, 0x8003)
		(CharacterSelectResponse, 0x8004)
		(CharacterCreateResponse, 0x8006)
		(CharacterDeleteResponse, 0x8007)
		(CharacterNameCheckResponse, 0x8011)
		(EmptyOperation0x8025, 0x8025)
		(EmptyOperation0x8026, 0x8026)
	)
}
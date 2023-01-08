#pragma once

namespace cebreiro
{
	class ServerConstant
	{
	public:
		ServerConstant() = delete;

		static constexpr uint64_t TWEPOCH = 1672498800000;

		static inline constexpr uint16_t LOGIN_PORT = 2106;
		static inline constexpr uint16_t GATEWAY_PORT = 2000;
		static const std::array<uint8_t, 256> CRYPTO_TABLE;

		// fixed in client 0x00596B75
		static inline constexpr uint32_t LOGIN_FIRST_KEY = 0;
		static inline constexpr uint32_t LOGIN_SECOND_KEY = 0x87546CA1;

		static inline constexpr int32_t GAME_VERSION = 2;
	};
}
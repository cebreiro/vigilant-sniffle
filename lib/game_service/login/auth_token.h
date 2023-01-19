#pragma once
#include <cstdint>
#include <array>
#include <string>

namespace cebreiro
{
	class AuthToken
	{
	public:
		AuthToken(int32_t key1, int32_t key2);
		AuthToken() = default;

		bool operator==(const AuthToken& other) const;
		bool operator!=(const AuthToken& other) const;

		auto ToString() const -> std::string;
		auto ToIntArray() const -> std::array<int32_t, 2>;

		static auto FromString(std::string_view str) -> AuthToken;

	private:
		int32_t _key1 = 0;
		int32_t _key2 = 0;
	};
}
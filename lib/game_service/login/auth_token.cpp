#include "auth_token.h"

#include <sstream>

namespace cebreiro
{
	AuthToken::AuthToken(int32_t key1, int32_t key2)
		: _key1(key1)
		, _key2(key2)
	{
	}

	bool AuthToken::operator==(const AuthToken& other) const
	{
		return _key1 == other._key1 && _key2 == other._key2;
	}

	bool AuthToken::operator!=(const AuthToken& other) const
	{
		return !operator==(other);
	}

	auto AuthToken::ToString() const -> std::string
	{
		std::ostringstream oss;
		oss << _key1 << _key2;

		return oss.str();
	}

	auto AuthToken::ToIntArray() const -> std::array<int32_t, 2>
	{
		return { _key1, _key2 };
	}
}

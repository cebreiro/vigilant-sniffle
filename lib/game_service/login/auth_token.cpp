#include "auth_token.h"

#include <vector>
#include <format>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>

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
		return std::format("{}:{}", static_cast<uint32_t>(_key1), static_cast<uint32_t>(_key2));
	}

	auto AuthToken::ToIntArray() const -> std::array<int32_t, 2>
	{
		return { _key1, _key2 };
	}

	auto AuthToken::FromString(std::string_view str) -> AuthToken
	{
		std::vector<std::string> result;
		boost::algorithm::split(result, str, boost::is_any_of(":"));

		if (result.size() < 2)
		{
			return {};
		}

		auto v1 = boost::lexical_cast<uint32_t>(result[0]);
		auto v2 = boost::lexical_cast<uint32_t>(result[1]);

		return AuthToken(static_cast<int32_t>(v1), static_cast<int32_t>(v2));
	}
}

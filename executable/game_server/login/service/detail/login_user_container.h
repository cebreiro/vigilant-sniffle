#pragma once
#include "lib/game_service/login/auth_token.h"

namespace cebreiro::login
{
	enum class LoginUserState
	{
		LoggedIn,
		GatewayTransition,
		GatewayConsumed,
		ZoneTransition,
		ZoneConsumed,
	};

	struct LoginUser
	{
		int64_t id = -1;
		LoginUserState state = LoginUserState::LoggedIn;
		AuthToken authenticationToken;
		std::string account;
		std::optional<int8_t> worldId = std::nullopt;
		std::optional<int32_t> zoneId = std::nullopt;
		std::optional<int64_t> characterId = std::nullopt;
		std::optional<uint64_t> expireTimePoint = std::nullopt;
		uint64_t loginTimePoint = 0;
	};

	class LoginUserContainer
	{
	public:
		bool Contains(int64_t id) const;
		bool Contains(const std::string& account) const;

		void Add(LoginUser item);
		void Remove(int64_t id);
		void Remove(const std::string& account);

		auto Find(int64_t id) const -> LoginUser*;
		auto Find(const std::string& account) const -> LoginUser*;
		auto Find(const AuthToken& token) const -> LoginUser*;

		void Foreach(const std::function<void(LoginUser&)>& fn);

	private:
		std::vector<std::shared_ptr<LoginUser>> _users;
		std::unordered_map<int64_t, std::shared_ptr<LoginUser>> _idIndexer;
		std::unordered_map<std::string, std::shared_ptr<LoginUser>> _accountIndexer;
	};
}

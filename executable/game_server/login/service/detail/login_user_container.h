#pragma once
#include "lib/game_service/login/auth_token.h"

namespace cebreiro::login
{
	struct LoginUser
	{
		int64_t id = -1;
		std::string account;
		uint64_t loginTimePoint = 0;
		std::optional<int8_t> worldId = std::nullopt;
		AuthToken authenticationToken;
		std::optional<uint64_t> expireTimePoint = std::nullopt;
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

#pragma once
#include "lib/common/execution/thread_pool.h"
#include "lib/game_service/login/login_service_interface.h"

namespace cebreiro
{
	class IServiceLocator;
}

namespace cebreiro::gamedb
{
	class GameDB;
}

namespace cebreiro::login
{
	class LoginUserContainer;

	class LoginService : public ILoginService
	{
	public:
		LoginService(const IServiceLocator& locator, gamedb::GameDB& gameDB);
		~LoginService();

		auto Login(std::string account, std::string password) -> Future<LoginResult> override;
		auto Logout(AuthToken authToken, int64_t accountId) -> Future<void> override;

		auto SetWorldId(AuthToken authToken, int8_t world) -> Future<bool> override;
		auto FindUser(AuthToken authToken) -> Future<std::optional<std::pair<int64_t, int8_t>>> override;

		void AddSubscriber(LoginServiceEventType type, const std::function<void(const LoginServiceEvent&)>& handler) override;

	private:
		auto Run() -> Future<void>;

	private:
		ThreadPool::Strand _strand;
		const IServiceLocator& _locator;
		gamedb::GameDB& _gameDB;
		std::unique_ptr<LoginUserContainer> _loginUserContainer;
		std::unordered_map<LoginServiceEventType, std::vector<std::function<void(const LoginServiceEvent&)>>> _eventSubscribers;

		bool _shutdown = false;
		Future<void> _runOperation;
	};
}
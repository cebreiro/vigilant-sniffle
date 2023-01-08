#pragma once
#include "lib/common/execution/thread_pool.h"
#include "service/login_service_interface.h"

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
		auto Logout(int64_t accountId) -> Future<void> override;

		auto AddGatewayAuthentication(int64_t accountId, int8_t world, std::array<int32_t, 2> token)
			-> Future<bool> override;

		auto PopGatewayAuthentication(std::array<int32_t, 2> token)
			-> Future<std::optional<std::pair<int64_t, int8_t>>> override;

	private:
		auto Run() -> Future<void>;

	private:
		ThreadPool::Strand _strand;
		const IServiceLocator& _locator;
		gamedb::GameDB& _gameDB;
		std::unique_ptr<LoginUserContainer> _loginUserContainer;

		bool _shutdown = false;
		Future<void> _runOperation;
	};
}
#include "login_service.h"

#include "lib/common/time_util.h"
#include "lib/common/execution/future.h"
#include "lib/common/execution/future_await.h"
#include "lib/common/execution/executor_await.h"
#include "lib/game_db/game_db.h"
#include "service/service_locator.h"
#include "login/service/detail/login_user_container.h"

namespace cebreiro::login
{
	LoginService::LoginService(const IServiceLocator& locator, gamedb::GameDB& gameDB)
		: _strand(ThreadPool::GetInstance().MakeStrand())
		, _locator(locator)
		, _gameDB(gameDB)
		, _loginUserContainer(std::make_unique<LoginUserContainer>())
	{
		_runOperation = Run();
	}

	LoginService::~LoginService()
	{
		std::atomic_ref(_shutdown).store(true);
		(void)_runOperation.Wait();
	}

	auto LoginService::Login(std::string account, std::string password) -> Future<LoginResult>
	{
		std::optional<gamebase::Account> result = 
			co_await _gameDB.FindAccount(account).ConfigureAwait(_strand);

		if (!result.has_value() || result->password != password)
		{
			co_return LoginResult{
				.errorCode = LoginResult::ErrorCode::FailInvalid,
			};
		}

		assert(result->account == account);

		if (_loginUserContainer->Contains(result->id))
		{
			co_return LoginResult{
				.errorCode = LoginResult::ErrorCode::FailDuplicated,
			};
		}

		LoginUser loginUserData{
			.id = result->id,
			.account = result->account,
			.loginTimePoint = Now(),
		};
		_loginUserContainer->Add(loginUserData);

		co_return LoginResult{
			.errorCode = LoginResult::ErrorCode::Success,
			.accountId = result->id,
		};
	}

	auto LoginService::Logout(int64_t accountId) -> Future<void>
	{
		co_await _strand;

		_loginUserContainer->Remove(accountId);
	}

	auto LoginService::AddGatewayAuthentication(int64_t accountId, int8_t world, std::array<int32_t, 2> token)
		-> Future<bool>
	{
		co_await _strand;

		LoginUser* loginUser = _loginUserContainer->Find(accountId);
		if (!loginUser)
		{
			LOGE(_locator.LogService(),
				std::format("fail to find login user. account: {}", accountId))
			co_return false;
		}

		if (loginUser->worldId.has_value())
		{
			LOGE(_locator.LogService(),
				std::format("login user already has world and token. account: {}, world[old:{}, new:{}]", 
					accountId, loginUser->worldId.value(), world))
			co_return false;
		}

		loginUser->worldId = world;
		loginUser->gatewayAuthenticationToken = token;
		loginUser->authenticationExpireTimePoint = Now() + 10000;

		co_return true;
	}

	auto LoginService::PopGatewayAuthentication(std::array<int32_t, 2> token)
		-> Future<std::optional<std::pair<int64_t, int8_t>>>
	{
		co_await _strand;

		LoginUser* user = _loginUserContainer->Find(token);
		if (!user)
		{
			LOGW(_locator.LogService(),
				std::format("fail to find login user from token. token: [{}:{}]", token[0], token[1]))
			co_return std::nullopt;
		}

		assert(user->worldId);
		user->gatewayAuthenticationToken.reset();

		co_return std::pair(user->id, user->worldId.value());
	}

	auto LoginService::Run() -> Future<void>
	{
		std::vector<int64_t> removeTargets;

		while (!std::atomic_ref(_shutdown).load())
		{
			co_await Delay(1000).ConfigureAwait(_strand);

			uint64_t now = Now();

			_loginUserContainer->Foreach([now, &removeTargets](const LoginUser& user)
				{
					if (user.gatewayAuthenticationToken.has_value())
					{
						if (now >= user.authenticationExpireTimePoint)
						{
							removeTargets.push_back(user.id);
						}
					}
				});

			if (!removeTargets.empty())
			{
				for (int64_t id : removeTargets)
				{
					_loginUserContainer->Remove(id);

					LOGW(_locator.LogService(),
						std::format("login is removed by token expiration. account: {}",
							id))
				}

				removeTargets.clear();
			}
		}
	}
}

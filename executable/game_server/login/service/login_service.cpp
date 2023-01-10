#include "login_service.h"

#include "lib/common/time_util.h"
#include "lib/common/execution/future.h"
#include "lib/common/execution/future_await.h"
#include "lib/common/execution/executor_await.h"
#include "lib/common/log/log_macro.h"
#include "lib/game_db/game_db.h"
#include "lib/game_service/service_locator_interface.h"
#include "lib/game_service/login/event/duplicate_login.h"
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
			DuplicateLogin duplicateLogin(result->id);

			for (const std::function<void(const LoginServiceEvent&)>& handler : _eventSubscribers[duplicateLogin.Type()])
			{
				handler(duplicateLogin);
			}

			_loginUserContainer->Remove(result->id);

			co_return LoginResult{
				.errorCode = LoginResult::ErrorCode::FailDuplicated,
			};
		}

		LoginUser loginUserData = [](const gamebase::Account& account) -> LoginUser
		{
			std::random_device rnd{};

			return LoginUser{
				.id = account.id,
				.account = account.account,
				.loginTimePoint = Now(),
				.authenticationToken = AuthToken(rnd(), rnd()),
			};
		}(result.value());
		_loginUserContainer->Add(loginUserData);

		co_return LoginResult{
			.errorCode = LoginResult::ErrorCode::Success,
			.authToken = loginUserData.authenticationToken,
			.accountId = result->id,
		};
	}

	auto LoginService::Logout(AuthToken authToken,int64_t accountId) -> Future<void>
	{
		co_await _strand;

		_loginUserContainer->Remove(accountId);
	}

	auto LoginService::SetWorldId(AuthToken authToken, int8_t world)
		-> Future<bool>
	{
		co_await _strand;

		LoginUser* loginUser = _loginUserContainer->Find(authToken);
		if (!loginUser)
		{
			LOGE(_locator.LogService(),
				std::format("fail to find login user. token: {}", authToken.ToString()))
			co_return false;
		}

		if (loginUser->worldId.has_value())
		{
			LOGE(_locator.LogService(),
				std::format("login user already has world. account: {}, world[old:{}, new:{}]", 
					loginUser->account, loginUser->worldId.value(), world))
			co_return false;
		}

		loginUser->worldId = world;
		loginUser->expireTimePoint = Now() + 10000;

		co_return true;
	}

	auto LoginService::FindUser(AuthToken authToken)
		-> Future<std::optional<std::pair<int64_t, int8_t>>>
	{
		co_await _strand;

		LoginUser* user = _loginUserContainer->Find(authToken);
		if (!user)
		{
			LOGW(_locator.LogService(),
				std::format("fail to find login user from token. token: [{}]", authToken.ToString()))
			co_return std::nullopt;
		}

		assert(user->worldId);
		user->expireTimePoint.reset();

		co_return std::pair(user->id, user->worldId.value());
	}

	void LoginService::AddSubscriber(LoginServiceEventType type, const std::function<void(const LoginServiceEvent&)>& handler)
	{
		_eventSubscribers[type].push_back(handler);
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
					if (user.expireTimePoint.has_value())
					{
						if (now >= user.expireTimePoint)
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

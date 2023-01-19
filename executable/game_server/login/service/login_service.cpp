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
				.state = LoginUserState::LoggedIn,
				.authenticationToken = AuthToken(rnd(), rnd()),
				.account = account.account,
				.loginTimePoint = Now(),
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

	auto LoginService::ConfigureGatewayTransitionState(AuthToken authToken, int8_t world)
		-> Future<bool>
	{
		co_await _strand;

		LoginUser* user = _loginUserContainer->Find(authToken);
		if (!user)
		{
			LOGE(_locator.LogService(),
				std::format("fail to find login user. token: {}", authToken.ToString()))
			co_return false;
		}

		if (user->state != LoginUserState::LoggedIn)
		{
			LOGE(_locator.LogService(),
				std::format("invalid state. account: {}, state: {}, token: {}", 
					user->account, static_cast<int32_t>(user->state), authToken.ToString()))
			co_return false;
		}

		if (user->worldId.has_value())
		{
			LOGE(_locator.LogService(),
				std::format("login user already has world. account: {}, world[old:{}, new:{}]", 
					user->account, user->worldId.value(), world))
			co_return false;
		}

		user->state = LoginUserState::GatewayTransition;
		user->worldId = world;
		user->expireTimePoint = Now() + 10000;

		co_return true;
	}

	auto LoginService::ConsumeGatewayTransitionState(AuthToken authToken)
		-> Future<GatewayTransitionMethod::ConsumeResult>
	{
		co_await _strand;

		LoginUser* user = _loginUserContainer->Find(authToken);
		if (!user)
		{
			LOGE(_locator.LogService(),
				std::format("fail to find login user from token. token: [{}]", authToken.ToString()))

			co_return GatewayTransitionMethod::ConsumeResult{
				.success = false,
			};
		}

		if (user->state != LoginUserState::GatewayTransition)
		{
			LOGE(_locator.LogService(),
				std::format("invalid state. account: {}, state: {}, token: {}",
					user->account, static_cast<int32_t>(user->state), authToken.ToString()))

			co_return GatewayTransitionMethod::ConsumeResult{
				.success = false,
			};
		}

		assert(user->worldId);
		user->state = LoginUserState::GatewayConsumed;
		user->expireTimePoint.reset();

		co_return GatewayTransitionMethod::ConsumeResult{
			.success = true,
			.accountId = user->id,
			.worldId = user->worldId.value(),
		};
	}

	auto LoginService::ConfigureZoneTransitionState(AuthToken authToken, ConfigureParam param) -> Future<bool>
	{
		co_await _strand;

		LoginUser* user = _loginUserContainer->Find(authToken);
		if (!user)
		{
			LOGE(_locator.LogService(),
				std::format("fail to find login user from token. token: [{}]", authToken.ToString()))

			co_return false;
		}

		if (user->state != LoginUserState::GatewayConsumed && user->state != LoginUserState::ZoneConsumed)
		{
			LOGE(_locator.LogService(),
				std::format("invalid state. account: {}, state: {}, token: {}",
					user->account, static_cast<int32_t>(user->state), authToken.ToString()))

			co_return false;
		}

		user->state = LoginUserState::ZoneTransition;
		user->zoneId = param.zoneId;
		user->characterId = param.characterId;
		user->expireTimePoint = Now() + 10000;

		co_return true;
	}

	auto LoginService::ConsumeZoneTransitionState(AuthToken authToken) -> Future<ZoneTransitionMethod::ConsumeResult>
	{
		co_await _strand;

		LoginUser* user = _loginUserContainer->Find(authToken);
		if (!user)
		{
			LOGE(_locator.LogService(),
				std::format("fail to find login user from token. token: [{}]", authToken.ToString()))

			co_return ZoneTransitionMethod::ConsumeResult{
				.success = false,
			};
		}

		if (user->state != LoginUserState::ZoneTransition)
		{
			LOGE(_locator.LogService(),
				std::format("invalid state. account: {}, state: {}, token: {}",
					user->account, static_cast<int32_t>(user->state), authToken.ToString()))

			co_return ZoneTransitionMethod::ConsumeResult{
				.success = false,
			};
		}

		assert(user->worldId);
		user->state = LoginUserState::GatewayConsumed;
		user->expireTimePoint.reset();

		co_return ZoneTransitionMethod::ConsumeResult{
			.success = true,
			.accountId = user->id,
			.worldId = user->worldId.value(),
			.zoneId = user->zoneId.value(),
			.characterId = user->characterId.value(),
		};
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

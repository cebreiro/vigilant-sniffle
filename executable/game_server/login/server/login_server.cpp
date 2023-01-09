#include "login_server.h"

#include "lib/common/stream/stream_util.h"
#include "lib/network/acceptor.h"
#include "lib/network/session.h"
#include "lib/game_service/service_locator_interface.h"
#include "config/server_constant.h"
#include "lib/common/log/log_macro.h"
#include "login/message/cs/cs_message_type.h"
#include "login/message/sc/hello.h"
#include "login/server/handler/cs_message_handler.h"
#include "login/server/handler/cs_message_handler_container.h"
#include "login/server/security/login_packet_decoder.h"
#include "login/server/security/login_packet_encoder.h"


namespace cebreiro::login
{
	LoginServer::LoginServer(const IServiceLocator& serviceLocator, network::NetworkExecutor& networkExecutor)
		: _locator(serviceLocator)
		, _networkExecutor(networkExecutor)
		, _acceptor(std::make_shared<network::Acceptor>(
			_networkExecutor, ServerConstant::LOGIN_PORT, *this))
	{
	}

	void LoginServer::Start()
	{
		_acceptor->StartAccept();

		_locator.LoginService().AddLoginReleaseEventHandler([this](int64_t id)
			{
				decltype(_sessions)::const_accessor accesor;

				if (_sessions.find(accesor, id))
				{
					accesor->second->session->Close();
				}
			});
	}

	void LoginServer::Stop()
	{
		_shutdown = true;
		_acceptor->Close();
	}

	void LoginServer::OnAccept(network::Acceptor& acceptor, std::shared_ptr<network::Socket> socket)
	{
		(void)acceptor;

		auto session = std::make_shared<network::Session>(
			network::Session::Id_t(_nextSessionId.fetch_add(1)),
			std::move(socket),
			std::make_unique<LoginPacketDecoder>(ServerConstant::LOGIN_FIRST_KEY, ServerConstant::LOGIN_SECOND_KEY),
			std::make_unique<LoginPacketEncoder>(ServerConstant::LOGIN_FIRST_KEY, ServerConstant::LOGIN_SECOND_KEY),
			*this);

		auto context = std::make_shared<LoginSessionContext>(LoginSessionContext{
			.session = session,
			.strand = ThreadPool::GetInstance().MakeStrand(),
			.state = LoginSessionState::Connected,
			.accountId = -1,});

		{
			uint64_t sessionId = session->Id().Value();

			decltype(_sessions)::accessor accessor;
			if (_sessions.insert(accessor, sessionId))
			{
				accessor->second = std::move(context);
			}
			else
			{
				LOGC(_locator.LogService(),
					std::format("fail to insert session. duplicated id: {}", sessionId))
					session->Close();
				return;
			}
		}

		LOGI(_locator.LogService(),
			std::format("accept session[{}:{}]",
				session->Id().Value(), session->RemoteAddress()))

		session->StartReceive();

		Hello hello(ServerConstant::LOGIN_FIRST_KEY, ServerConstant::LOGIN_SECOND_KEY);
		session->Send(hello.Serialize(), false);
	}

	void LoginServer::OnError(network::Acceptor& acceptor, const network::error_t& error)
	{
		if (_shutdown)
		{
			LOGI(_locator.LogService(), 
				std::format("acceptor is going shutdown. error: {}", error.message()))
		}
		else
		{
			LOGE(_locator.LogService(),
				std::format("acceptr error. error: {}", error.message()))
			acceptor.Close();
		}
	}

	void LoginServer::UnhandledException(network::Acceptor& acceptor, const std::exception& exception)
	{
		(void)acceptor;
		(void)exception;

		LOGC(_locator.LogService(),
			std::format("acceptor unhandled exception: {}", exception.what()))
	}

	void LoginServer::OnSend(network::Session& session, network::Buffer& buffer)
	{
		(void)session;
		(void)buffer;
	}

	void LoginServer::OnReceive(network::Session& session, network::Buffer& buffer)
	{
		LOGT(_locator.LogService(),
			std::format("session[{}:{}] receive buffer: {}",
				session.Id().Value(), session.RemoteAddress(), cebreiro::ToString(buffer.Data(), buffer.Size())))

		auto context = [this, id = session.Id().Value()]() -> std::shared_ptr<LoginSessionContext>
		{
			decltype(_sessions)::const_accessor accessor;

			if (_sessions.find(accessor, id))
			{
				return accessor->second;
			}
			else
			{
				return nullptr;
			}
		}();

		if (!context)
		{
			LOGW(_locator.LogService(),
				std::format("fail to find login session context. session[{}:{}]", 
					session.Id().Value(), session.RemoteAddress()))
			return;
		}

		context->strand.Post([this, context, buffer = std::move(buffer)]()
			{
				try
				{
					StreamReader reader(buffer.Data(), buffer.Size(), 2);
					CSMessageType messageType = static_cast<CSMessageType>(reader.ReadInt8());

					const auto& handler = CSMessageHandlerContainer::Find(messageType);
					if (!handler.has_value())
					{
						LOGW(_locator.LogService(),
							std::format("unhandled message: {}, bytes: {}",
								ToString(messageType), cebreiro::ToString(buffer.Data(), buffer.Size())))
						return;
					}

					std::visit([&]<typename T>(const T& value)
					{
						if constexpr (std::is_same_v<T, ICSMessageHandler*>)
						{
							value->Handle(_locator, *context, reader);
						}
						else if constexpr (std::is_same_v<T, ICSMessageAsyncHandler*>)
						{
							value->Handle(_locator, context, reader)
								.ContinuationWith([this, context](Future<void>& future)
								{
									try
									{
										future.Get();
									}
									catch (const std::exception& e)
									{
										HandleMessageException(*context, e);
									}
								});
						}
						else
						{
							static_assert(!sizeof(T), "not implement");
						}

					}, handler.value());
				}
				catch (const std::exception& e)
				{
					HandleMessageException(*context, e);
				}
			});
	}

	void LoginServer::OnError(network::Session& session, const network::error_t& error)
	{
		LOGW(_locator.LogService(),
			std::format("session[{}:{}] io error: {}",
				session.Id().Value(), session.RemoteAddress(), error.message()))

		RemoveSession(session);
	}

	void LoginServer::UnhandledException(network::Session& session, const std::exception& exception)
	{
		LOGC(_locator.LogService(),
			std::format("session[{}:{}] unhandled exception: {}",
				session.Id().Value(), session.RemoteAddress(), exception.what()))

		RemoveSession(session);
	}

	void LoginServer::HandleMessageException(const LoginSessionContext& context, const std::exception& exception)
	{
		LOGE(_locator.LogService(),
			std::format("handle message exception. session[{}:{}], exception: {}", 
				context.session->Id().Value(), context.session->RemoteAddress(), exception.what()))

		RemoveSession(*context.session);
	}

	void LoginServer::RemoveSession(const network::Session& session)
	{
		std::shared_ptr<LoginSessionContext> context = [&]() -> std::shared_ptr<LoginSessionContext>
		{
			std::shared_ptr<LoginSessionContext> result = {};
			{
				decltype(_sessions)::const_accessor accessor;

				if (_sessions.find(accessor, session.Id().Value()))
				{
					result = std::move(accessor->second);
					_sessions.erase(accessor);
				}
			}

			return result;
		}();

		if (!context)
		{
			return;
		}

		context->strand.Post([this, context]()
			{
				if (context->state == LoginSessionState::LoggedIn)
				{
					(void)_locator.LoginService().Logout(context->authToken, context->accountId);
				}
			});
	}
}

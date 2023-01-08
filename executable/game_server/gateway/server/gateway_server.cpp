#include "gateway_server.h"

#include "handler/cs_message_handler_container.h"
#include "lib/common/log/log_macro.h"
#include "lib/common/stream/stream_util.h"
#include "lib/game_base/network/packet_reader.h"
#include "lib/network/acceptor.h"
#include "lib/network/session.h"
#include "config/server_constant.h"
#include "service/service_locator.h"
#include "gateway/message/cs/cs_message_type.h"
#include "gateway/server/gateway_session_context.h"
#include "gateway/server/handler/cs_message_handler.h"
#include "gateway/server/security/gateway_packet_decoder.h"
#include "gateway/server/security/gateway_packet_encoder.h"

namespace cebreiro::gateway
{
	GatewayServer::GatewayServer(const IServiceLocator& serviceLocator, network::NetworkExecutor& networkExecutor)
		: _locator(serviceLocator)
		, _networkExecutor(networkExecutor)
		, _acceptor(std::make_shared<network::Acceptor>(
			_networkExecutor, ServerConstant::GATEWAY_PORT, *this))
	{
	}

	void GatewayServer::Start()
	{
		_acceptor->StartAccept();
	}

	void GatewayServer::Stop()
	{
		_shutdown = true;
		_acceptor->Close();
	}

	void GatewayServer::OnAccept(network::Acceptor& acceptor, std::shared_ptr<network::Socket> socket)
	{
		(void)acceptor;

		auto session = std::make_shared<network::Session>(
			network::Session::Id_t(_nextSessionId.fetch_add(1)),
			std::move(socket),
			std::make_unique<GatewayPacketDecoder>(),
			std::make_unique<GatewayPacketEncoder>(),
			*this);

		auto context = std::make_shared<GatewaySessionContext>(GatewaySessionContext{
			.session = session,
			.strand = ThreadPool::GetInstance().MakeStrand(),
			.state = GatewaySessionState::Connected,
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
	}

	void GatewayServer::OnError(network::Acceptor& acceptor, const network::error_t& error)
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

	void GatewayServer::UnhandledException(network::Acceptor& acceptor, const std::exception& exception)
	{
		(void)acceptor;
		(void)exception;

		LOGC(_locator.LogService(),
			std::format("acceptor unhandled exception: {}", exception.what()))
	}

	void GatewayServer::OnSend(network::Session& session, network::Buffer& buffer)
	{
		(void)session;
		(void)buffer;
	}

	void GatewayServer::OnReceive(network::Session& session, network::Buffer& buffer)
	{
		LOGT(_locator.LogService(),
			std::format("session[{}:{}] receive buffer: {}",
				session.Id().Value(), session.RemoteAddress(), cebreiro::ToString(buffer.Data(), buffer.Size())))

		auto context = [this, id = session.Id().Value()]() -> std::shared_ptr<GatewaySessionContext>
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
					gamebase::PacketReader reader(buffer);
					CSMessageType messageType = static_cast<CSMessageType>(reader.ReadInt32());

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

	void GatewayServer::OnError(network::Session& session, const network::error_t& error)
	{
		(void)session;
		(void)error;

		LOGW(_locator.LogService(),
			std::format("session[{}:{}] io error: {}",
				session.Id().Value(), session.RemoteAddress(), error.message()))
	}

	void GatewayServer::UnhandledException(network::Session& session, const std::exception& exception)
	{
		(void)session;
		(void)exception;

		LOGC(_locator.LogService(),
			std::format("session[{}:{}] unhandled exception: {}",
				session.Id().Value(), session.RemoteAddress(), exception.what()))
	}

	void GatewayServer::HandleMessageException(const GatewaySessionContext& context, const std::exception& exception) const
	{
		LOGE(_locator.LogService(),
			std::format("handle message exception. session[{}:{}], exception: {}",
				context.session->Id().Value(), context.session->RemoteAddress(), exception.what()))
	}
}

#include "zone_server.h"

#include "lib/common/log/log_macro.h"
#include "lib/common/stream/stream_util.h"
#include "lib/game_base/network/packet_reader.h"
#include "lib/game_service/service_locator_interface.h"
#include "lib/network/acceptor.h"
#include "zone/message/cs/cs_message_type.h"
#include "zone/server/zone_session_context.h"
#include "zone/server/handler/cs_message_handler.h"
#include "zone/server/handler/cs_message_handler_container.h"
#include "zone/server/security/zone_packet_decoder.h"
#include "zone/server/security/zone_packet_encoder.h"

namespace cebreiro::zone
{
	ZoneServer::ZoneServer(const IServiceLocator& serviceLocator, network::NetworkExecutor& networkExecutor,
		uint16_t port, std::shared_ptr<Zone> zone)
		: _locator(serviceLocator)
		, _networkExecutor(networkExecutor)
		, _acceptor(std::make_shared<network::Acceptor>(
			_networkExecutor, port, *this))
		, _zone(std::move(zone))
	{
	}

	void ZoneServer::Start()
	{
		_acceptor->StartAccept();
	}

	void ZoneServer::Stop()
	{
		_shutdown = true;
		_acceptor->Close();
	}

	void ZoneServer::OnAccept(network::Acceptor& acceptor, std::shared_ptr<network::Socket> socket)
	{
		(void)acceptor;

		auto session = std::make_shared<network::Session>(
			network::Session::Id_t(_nextSessionId.fetch_add(1)),
			std::move(socket),
			std::make_unique<ZonePacketDecoder>(),
			std::make_unique<ZonePacketEncoder>(),
			*this);
		auto context = std::make_shared<ZoneSessionContext>(ZoneSessionContext{
			.session = session,
			.strand = ThreadPool::GetInstance().MakeStrand(),
			.state = ZoneSessionState::Connected,
			.zone = *_zone,
		});
		{
			decltype(_sessions)::accessor accessor;
			if (_sessions.insert(accessor, session->Id()))
			{
				accessor->second = context;

				std::lock_guard lock(_sessionsForIterationMutex);
				_sessionsForIteration.push_back(std::move(context));
			}
			else
			{
				LOGC(_locator.LogService(),
					std::format("fail to insert session. duplicated id: {}, address: {}",
						session->Id().Value(), session->RemoteAddress()))
					session->Close();
				return;
			}
		}

		LOGI(_locator.LogService(),
			std::format("accept session[{}:{}]",
				session->Id().Value(), session->RemoteAddress()))

		session->StartReceive();
	}

	void ZoneServer::OnError(network::Acceptor& acceptor, const network::error_t& error)
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

	void ZoneServer::UnhandledException(network::Acceptor& acceptor, const std::exception& exception)
	{
		(void)acceptor;
		(void)exception;

		LOGC(_locator.LogService(),
			std::format("acceptor unhandled exception: {}", exception.what()))
	}

	void ZoneServer::OnSend(network::Session& session, network::Buffer& buffer)
	{
		(void)session;
		(void)buffer;
	}

	void ZoneServer::OnReceive(network::Session& session, network::Buffer& buffer)
	{
		LOGT(_locator.LogService(),
			std::format("session[{}:{}] receive buffer: {}",
				session.Id().Value(), session.RemoteAddress(), cebreiro::ToString(buffer.Data(), buffer.Size())))

		auto context = [this, id = session.Id()]() -> std::shared_ptr<ZoneSessionContext>
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

	void ZoneServer::OnError(network::Session& session, const network::error_t& error)
	{
		LOGW(_locator.LogService(),
			std::format("session[{}:{}] io error: {}",
				session.Id().Value(), session.RemoteAddress(), error.message()))

		RemoveSession(session);
	}

	void ZoneServer::UnhandledException(network::Session& session, const std::exception& exception)
	{
		LOGC(_locator.LogService(),
			std::format("session[{}:{}] unhandled exception: {}",
				session.Id().Value(), session.RemoteAddress(), exception.what()))

		RemoveSession(session);
	}

	void ZoneServer::HandleMessageException(const ZoneSessionContext& context, const std::exception& exception)
	{
		LOGE(_locator.LogService(),
			std::format("handle message exception. session[{}:{}], exception: {}",
				context.session->Id().Value(), context.session->RemoteAddress(), exception.what()))

		RemoveSession(*context.session);
	}

	void ZoneServer::RemoveSession(network::Session& session)
	{
		(void)session;
	}
}

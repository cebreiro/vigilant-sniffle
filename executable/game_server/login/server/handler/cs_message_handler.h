#pragma once
#include "lib/common/stream/stream_reader.h"
#include "lib/common/execution/future.h"
#include "lib/common/execution/thread_pool.h"
#include "login/message/cs/cs_message_type.h"

namespace cebreiro
{
	class Executor;
	class IServiceLocator;
}

namespace cebreiro::network
{
	class Session;
}

namespace cebreiro::login
{
	struct LoginSessionContext;

	class ICSMessageHandler
	{
	public:
		virtual ~ICSMessageHandler() = default;

		virtual void Handle(const IServiceLocator& locator, LoginSessionContext& context, StreamReader& reader) = 0;
	};

	class ICSMessageAsyncHandler
	{
	public:
		virtual ~ICSMessageAsyncHandler() = default;

		virtual auto Handle(const IServiceLocator& locator, std::shared_ptr<LoginSessionContext> context, StreamReader& reader)
			-> Future<void> = 0;
	};

	template <typename T> requires std::derived_from<T, IDeserializable>
	class CSMessageHandler : public ICSMessageHandler
	{
	public:
		static constexpr CSMessageType TYPE = T::TYPE;

		void Handle(const IServiceLocator& locator, LoginSessionContext& context, StreamReader& reader) final
		{
			T message = {};
			message.Deserialize(reader);

			this->OnMessage(locator, context, message);
		}

		virtual void OnMessage(const IServiceLocator& locator, LoginSessionContext& context, const T& message) = 0;
	};

	template <typename T> requires std::derived_from<T, IDeserializable>
	class CSMessageAsyncHandler : public ICSMessageAsyncHandler
	{
	public:
		static constexpr CSMessageType TYPE = T::TYPE;

		auto Handle(const IServiceLocator& locator, std::shared_ptr<LoginSessionContext> context, StreamReader& reader)
			-> Future<void> final
		{
			T message = {};
			message.Deserialize(reader);

			co_await this->OnMessage(locator, *context, message);
			co_return;
		}

		virtual auto OnMessage(const IServiceLocator& locator, LoginSessionContext& context, const T& message)
			-> Future<void> = 0;
	};
}
#pragma once
#include "login/message/cs/cs_message_type.h"

namespace cebreiro::login
{
	class ICSMessageHandler;
	class ICSMessageAsyncHandler;

	class CSMessageHandlerAutoRegistry
	{
	protected:
		CSMessageHandlerAutoRegistry(CSMessageType type, ICSMessageHandler* handler);
		CSMessageHandlerAutoRegistry(CSMessageType type, ICSMessageAsyncHandler* handler);
	};

	template <typename T>
	class CSMessageHandlerAutoRegistryT : public CSMessageHandlerAutoRegistry
	{
	public:
		CSMessageHandlerAutoRegistryT()
			: CSMessageHandlerAutoRegistry(T::TYPE, GetInstance())
		{
		}
		~CSMessageHandlerAutoRegistryT() = default;

	private:
		static auto GetInstance() -> T*
		{
			static T instance;
			return &instance;
		}
	};
}
#pragma once
#include "zone/message/cs/cs_message_type.h"

namespace cebreiro::zone
{
	class ICSMessageHandler;
	class ICSMessageAsyncHandler;

	class CSMessageHandlerAutoRegistry
	{
	public:
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

#pragma once
#include "zone/message/cs/cs_message_type.h"

namespace cebreiro::zone
{
	class ICSMessageHandler;
	class ICSMessageAsyncHandler;

	class CSMessageHandlerContainer
	{
	public:
		using value_type = std::variant<ICSMessageHandler*, ICSMessageAsyncHandler*>;

	public:
		CSMessageHandlerContainer() = delete;

		static void Add(CSMessageType type, value_type value);
		static auto Find(CSMessageType type) -> std::optional<value_type>;
	};
}

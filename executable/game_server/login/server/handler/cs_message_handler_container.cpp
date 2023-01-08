#include "cs_message_handler_container.h"

namespace cebreiro::login
{
	using container_type = std::unordered_map<CSMessageType, CSMessageHandlerContainer::value_type>;

	namespace
	{
		auto GetContainer() -> container_type&
		{
			static container_type instance;
			return instance;
		}
	}

	void CSMessageHandlerContainer::Add(CSMessageType type, value_type value)
	{
		[[maybe_unused]] bool result = GetContainer().try_emplace(type, value).second;
		assert(result);
	}

	auto CSMessageHandlerContainer::Find(CSMessageType type) -> std::optional<value_type>
	{
		container_type& container = GetContainer();

		auto iter = container.find(type);
		if (iter == container.end())
		{
			return std::nullopt;
		}

		return iter->second;
	}
}

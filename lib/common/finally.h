#pragma once
#include <functional>

namespace cebreiro
{
	class Finally
	{
	public:
		explicit Finally(std::function<void()> action);
		~Finally();

	private:
		std::function<void()> _action;
	};
}
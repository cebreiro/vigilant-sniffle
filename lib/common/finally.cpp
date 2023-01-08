#include "finally.h"

namespace cebreiro
{
	Finally::Finally(std::function<void()> action)
		: _action(std::move(action))
	{
	}

	Finally::~Finally()
	{
		if (_action)
		{
			_action();
		}
	}
}

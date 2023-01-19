#include "component_base.h"

namespace cebreiro::zone
{
	ComponentBase::ComponentBase(GameObject& object)
		: _object(object)
	{
	}

	void ComponentBase::Tick(time_point_t now)
	{
		if (_doTick)
		{
			this->OnTick(now);
		}
	}

	void ComponentBase::SetDoTick(bool value)
	{
		_doTick = value;
	}

	void ComponentBase::OnTick(time_point_t now)
	{
		(void)now;
	}
}

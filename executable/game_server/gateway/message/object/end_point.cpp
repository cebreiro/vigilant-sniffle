#include "end_point.h"

namespace cebreiro::gateway
{
	EndPoint::EndPoint(std::string address, uint16_t port)
		: _address(std::move(address))
		, _port(port)
	{
	}

	auto EndPoint::Serialize() const -> gamebase::SerializedObject
	{
		gamebase::SerializedObject object;

		object.WriteInt32(static_cast<int32_t>(_port));
		object.WriteString(_address);

		return object;
	}
}

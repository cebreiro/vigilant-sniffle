#pragma once
#include "lib/game_base/network/serialized_object.h"

namespace cebreiro::gateway
{
	class EndPoint
	{
	public:
		EndPoint() = default;
		explicit EndPoint(std::string address, uint16_t port);

		auto Serialize() const -> gamebase::SerializedObject;

	private:
		std::string _address;
		uint64_t _port = 0;
	};
}
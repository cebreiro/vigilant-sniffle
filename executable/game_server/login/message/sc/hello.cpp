#include "hello.h"

#include "lib/common/stream/stream_writer.h"

namespace cebreiro::login
{
	Hello::Hello(uint32_t key1, uint32_t key2)
		: _key1(key1)
		, _key2(key2)
	{
	}

	auto Hello::GetType() const -> SCMessageType
	{
		return SCMessageType::Hello;
	}

	auto Hello::GetBodySize() const -> size_t
	{
		return sizeof(_key1) + sizeof(_key2);
	}

	void Hello::SerializeBody(StreamWriter& writer) const
	{
		writer.WriteUInt32(_key1);
		writer.WriteUInt32(_key2);
	}
}

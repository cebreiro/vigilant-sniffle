#include "buffer.h"

namespace cebreiro::network
{
	Buffer::Buffer(std::shared_ptr<char[]> buffer, size_t offset, size_t used)
		: _buffer(std::move(buffer))
		, _offset(offset)
		, _used(used)
	{
	}

	Buffer::~Buffer()
	{
	}

	bool Buffer::IsValid() const
	{
		return _buffer.operator bool();
	}

	auto Buffer::Data() -> char*
	{
		return _buffer.get() + _offset;
	}

	auto Buffer::Data() const -> const char*
	{
		return _buffer.get() + _offset;
	}

	auto Buffer::Size() const -> size_t
	{
		return _used;
	}
}

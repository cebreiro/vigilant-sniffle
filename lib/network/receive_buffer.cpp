#include "receive_buffer.h"

#include <cassert>
#include <format>

#include "lib/common/stacktrace_exception.h"


namespace cebreiro::network
{
	ReceiveBuffer::ReceiveBuffer(ReceiveBuffer&& rhs) noexcept
	{
		(void)operator=(std::move(rhs));
	}

	ReceiveBuffer& ReceiveBuffer::operator=(ReceiveBuffer&& rhs) noexcept
	{
		_buffer = std::move(rhs._buffer);
		_size = rhs._size;
		_offset = rhs._offset;
		_received = rhs._received;

		rhs._size = 0;
		rhs._offset = 0;
		rhs._received = 0;

		return *this;
	}

	ReceiveBuffer::ReceiveBuffer(size_t size)
		: _buffer(std::make_shared<char[]>(size))
		, _size(size)
	{
	}

	ReceiveBuffer::~ReceiveBuffer()
	{
	}

	bool ReceiveBuffer::IsFull() const
	{
		assert(IsValid());

		if (_received == 0)
		{
			return false;
		}

		return _size == (_offset + _received);
	}

	bool ReceiveBuffer::IsValid() const
	{
		return _size != _offset;
	}

	auto ReceiveBuffer::SliceFront(size_t size) -> Buffer
	{
		if (size > _received)
		{
			throw StacktraceException(std::format("size error. request: {}, used: {}", size, _received));
		}

		Buffer buffer(_buffer, _offset, size);

		_offset += size;
		_received -= size;

		return buffer;
	}

	void ReceiveBuffer::Resize(size_t size)
	{
		if (size == 0)
		{
			assert(false);
			return;
		}

		ReceiveBuffer other(size);

		if (_received > 0)
		{
			size_t count = std::min(_received, size);

			std::copy_n(_buffer.get() + _offset, count, other._buffer.get());
			other._received = count;
		}

		std::swap(*this, other);
	}

	void ReceiveBuffer::Reset()
	{
		assert(_received == 0);

		_buffer = std::make_shared<char[]>(_size);
		_offset = 0;
		_received = 0;
	}

	auto ReceiveBuffer::Data() -> char*
	{
		return _buffer.get() + _offset;
	}

	auto ReceiveBuffer::Data() const -> const char*
	{
		return _buffer.get() + _offset;
	}

	auto ReceiveBuffer::Size() const -> size_t
	{
		assert(_size >= _offset);
		return _size - _offset;
	}

	auto ReceiveBuffer::ReceiveSize() const -> size_t
	{
		return _received;
	}

	auto ReceiveBuffer::GetBufferMaxSize() const -> size_t
	{
		return _size;
	}

	void ReceiveBuffer::AddReceiveSize(size_t received)
	{
		_received += received;

		assert(_offset + _received <= _size);
	}
}

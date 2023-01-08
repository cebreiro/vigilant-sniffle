#pragma once
#include <memory>

#include "lib/network/buffer.h"

namespace cebreiro::network
{
	class ReceiveBuffer
	{
	public:
		ReceiveBuffer(const ReceiveBuffer&) = delete;
		ReceiveBuffer& operator=(const ReceiveBuffer&) = delete;

		ReceiveBuffer() = default;
		ReceiveBuffer(ReceiveBuffer&& rhs) noexcept;
		ReceiveBuffer& operator= (ReceiveBuffer&& rhs) noexcept;

		explicit ReceiveBuffer(size_t size);
		~ReceiveBuffer();

		bool IsFull() const;
		bool IsValid() const;

		auto SliceFront(size_t size) -> Buffer;
		void Resize(size_t size);
		void Reset();

		auto Data() -> char*;
		auto Data() const -> const char*;
		auto Size() const -> size_t;
		auto ReceiveSize() const -> size_t;

		auto GetBufferMaxSize() const -> size_t;

		void AddReceiveSize(size_t received);

	private:
		std::shared_ptr<char[]> _buffer;
		size_t _size = 0;
		size_t _offset = 0;
		size_t _received = 0;
	};
}
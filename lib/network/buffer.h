#pragma once
#include <memory>
#include <vector>

namespace cebreiro::network
{
	class Buffer
	{
	public:
		Buffer() = default;
		Buffer(const Buffer&) = default;
		Buffer(Buffer&&) noexcept = default;
		Buffer& operator=(const Buffer&) = default;
		Buffer& operator=(Buffer&&) noexcept = default;

		Buffer(std::shared_ptr<char[]> buffer, size_t offset, size_t used);
		~Buffer();

		bool IsValid() const;

		auto Data() -> char*;
		auto Data() const -> const char*;
		auto Size() const -> size_t;

	private:
		std::shared_ptr<char[]> _buffer;
		size_t _offset = 0;
		size_t _used = 0;
	};
}
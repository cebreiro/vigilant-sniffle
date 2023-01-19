#pragma once
#include <cstdint>

namespace cebreiro
{
	template <typename T, typename ID = uint64_t>
	class ClassId
	{
	public:
		template <typename U>
		static auto GetId() -> ID;

	private:
		static ID _nextId;
	};

	template <typename T, typename ID>
	template <typename U>
	auto ClassId<T, ID>::GetId() -> ID
	{
		static ID id{ _nextId++ };
		return id;
	}

	template <typename T, typename ID>
	ID ClassId<T, ID>::_nextId = 0;
}
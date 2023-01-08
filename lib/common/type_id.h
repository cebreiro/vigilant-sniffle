#pragma once
#include <cstdint>

namespace cebreiro
{
	template <typename T, typename ID = uint64_t>
	struct TypeId
	{
	public:
		template <typename U>
		static ID GetId();

	private:
		static ID _NEXT_ID;
	};

	template <typename T, typename ID>
	template <typename U>
	ID TypeId<T, ID>::GetId()
	{
		static ID id{ _NEXT_ID++ };
		return id;
	}

	template <typename T, typename ID>
	ID TypeId<T, ID>::_NEXT_ID = 0;
}
#pragma once
#include <functional>
#include <type_traits>
#include <tuple>
#include <utility>

namespace cebreiro
{
	template <typename T, typename = void>
	struct IsOptional : std::false_type {};

	template <typename T>
	struct IsOptional<T, std::void_t<typename T::value_type>>
	{
		static constexpr bool value = std::is_same_v<T, std::optional<typename T::value_type>>;
	};
}
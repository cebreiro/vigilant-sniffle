#pragma once
#include <concepts>

namespace cebreiro
{
	template <std::integral T, typename Tag>
	class Identifier
	{
	public:
		using value_type = T;

	public:
		Identifier() = default;
		Identifier(const Identifier&) = default;
		Identifier(Identifier&&) noexcept = default;
		Identifier& operator=(const Identifier&) = default;
		Identifier& operator=(Identifier&&) noexcept = default;

		explicit Identifier(T value);
		~Identifier() = default;

		auto Value() const -> T;

		bool operator==(const Identifier& other) const;
		bool operator!=(const Identifier& other) const;
		bool operator<(const Identifier& other) const;

	private:
		T _value = 0;
	};

	template <std::integral T, typename Tag>
	Identifier<T, Tag>::Identifier(T value)
		: _value(value)
	{
	}

	template <std::integral T, typename Tag>
	auto Identifier<T, Tag>::Value() const -> T
	{
		return _value;
	}

	template <std::integral T, typename Tag>
	bool Identifier<T, Tag>::operator==(const Identifier& other) const
	{
		return _value == other._value;
	}

	template <std::integral T, typename Tag>
	bool Identifier<T, Tag>::operator!=(const Identifier& other) const
	{
		return _value != other._value;
	}

	template <std::integral T, typename Tag>
	bool Identifier<T, Tag>::operator<(const Identifier& other) const
	{
		return _value < other._value;
	}
}

namespace std
{
	template <std::integral T, typename Tag>
	struct hash<cebreiro::Identifier<T, Tag>>
	{
		auto operator()(const cebreiro::Identifier<T, Tag>& id) const -> size_t
		{
			return hash<T>()(id.Value());
		}
	};
}
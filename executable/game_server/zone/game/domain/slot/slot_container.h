#pragma once

namespace cebreiro::zone
{
	template <typename T, int32_t X, int32_t Y, int32_t Z>
	class SlotContainer
	{
	public:
		static constexpr int32_t WIDTH = X;
		static constexpr int32_t HEIGHT = X;
		static constexpr int32_t PAGE = X;

		struct Position;
		struct Range;

	public:
		SlotContainer();

		bool AllOf(T value, const Range& range) const;

		auto GetItem(const Position& position) const -> T;
		auto GetItems(const Range& range) const -> boost::container::small_vector<T, 8>;

		void Set(T value, const Range& range);

		void Clear();

	private:
		std::array<std::array<std::array<T, WIDTH>, HEIGHT>, PAGE> _pages = {};
	};

	template <typename T, int32_t X, int32_t Y, int32_t Z>
	struct SlotContainer<T, X, Y, Z>::Position
	{
		int32_t page = 0;
		int32_t x = 0;
		int32_t y = 0;

		bool IsValid() const
		{
			if (page < 0 || page >= PAGE)
			{
				return false;
			}

			if (y < 0 || y >= HEIGHT)
			{
				return false;
			}

			if (x < 0 || x >= WIDTH)
			{
				return false;
			}

			return true;
		}
	};

	template <typename T, int32_t X, int32_t Y, int32_t Z>
	struct SlotContainer<T, X, Y, Z>::Range
	{
		int32_t page = 0;
		int32_t x = 0;
		int32_t y = 0;
		int32_t width = 0;
		int32_t height = 0;

		bool IsValid() const
		{
			Position position{ page, x, y };

			if (!position.IsValid())
			{
				return false;
			}

			if (width < 0 || height < 0)
			{
				return false;
			}

			if (x + width > WIDTH || y + height > HEIGHT)
			{
				return false;
			}

			return true;
		}
	};

	template <typename T, int32_t X, int32_t Y, int32_t Z>
	SlotContainer<T, X, Y, Z>::SlotContainer()
	{
		Clear();
	}

	template <typename T, int32_t X, int32_t Y, int32_t Z>
	bool SlotContainer<T, X, Y, Z>::AllOf(T value, const Range& range) const
	{
		assert(range.IsValid());

		const auto& page = _pages[range.page];
		for (int8_t y = range.y; y < range.y + range.height; ++y)
		{
			for (int8_t x = range.x; x < range.x + range.width; ++x)
			{
				if (page[y][x] != value)
				{
					return false;
				}
			}
		}

		return true;
	}

	template <typename T, int32_t X, int32_t Y, int32_t Z>
	auto SlotContainer<T, X, Y, Z>::GetItem(const Position& position) const -> T
	{
		assert(position.IsValid());

		return _pages[position.page][position.y][position.x];
	}

	template <typename T, int32_t X, int32_t Y, int32_t Z>
	auto SlotContainer<T, X, Y, Z>::GetItems(const Range& range) const -> boost::container::small_vector<T, 8>
	{
		assert(range.IsValid());

		boost::container::small_vector<T, 8> result;

		auto& page = _pages[range.page];
		for (int8_t y = range.y; y < range.y + range.height; ++y)
		{
			for (int8_t x = range.x; x < range.x + range.width; ++x)
			{
				result.push_back(page[y][x]);
			}
		}

		sr::sort(result);
		result.erase(std::unique(result.begin(), result.end()), result.end());

		return result;
	}

	template <typename T, int32_t X, int32_t Y, int32_t Z>
	void SlotContainer<T, X, Y, Z>::Set(T value, const Range& range)
	{
		assert(range.IsValid());

		auto& page = _pages[range.page];
		for (int8_t y = range.y; y < range.y + range.height; ++y)
		{
			for (int8_t x = range.x; x < range.x + range.width; ++x)
			{
				page[y][x] = value;
			}
		}
	}

	template <typename T, int32_t X, int32_t Y, int32_t Z>
	void SlotContainer<T, X, Y, Z>::Clear()
	{
		_pages.fill({});
	}
}
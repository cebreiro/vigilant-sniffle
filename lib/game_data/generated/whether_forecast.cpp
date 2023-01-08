/**********************************************************
         AUTO GENERATED FILE BY sox_code_generator
                   DO NOT EDIT THIS FILE
**********************************************************/
#include "whether_forecast.h"

#include "lib/common/stream/stream_reader.h"
#include "lib/game_base/data/sox/sox_file.h"
#include "lib/game_data/game_data_registry.h"

namespace cebreiro::gamedata
{
	[[maybe_unused]]
	static GameDataRegistry<WhetherForecastTable> registry;

	WhetherForecast::WhetherForecast(StreamReader& reader)
	{
		index = reader.ReadInt32();
		whetherType = reader.ReadInt32();
		lightType = reader.ReadInt32();
		density = reader.ReadInt32();
		cloudType = reader.ReadInt32();
		fog = reader.ReadInt32();
		fogRate = reader.ReadFloat32();
		fogColorR = reader.ReadInt32();
		fogColorG = reader.ReadInt32();
		fogColorB = reader.ReadInt32();
		cloudA = reader.ReadInt32();
		cloudB = reader.ReadInt32();
	}

	void WhetherForecastTable::LoadFromFile(const std::filesystem::path& path)
	{
		gamebase::SoxFile fileData(path / "WHETHER_FORECAST.sox");
		StreamReader reader(fileData.gameData.data(), fileData.gameData.size());

		_vector.reserve(fileData.rowCount);
		for (int32_t i = 0; i < fileData.rowCount; ++i)
		{
			_vector.emplace_back(reader);
		}

		for (const WhetherForecast& data : _vector)
		{
			_umap[data.index] = &data;
		}
	}

	auto WhetherForecastTable::Find(int32_t index) const -> const WhetherForecast*
	{
		auto iter = _umap.find(index);
		return iter != _umap.end() ? iter->second : nullptr;
	}

	auto WhetherForecastTable::Get() const -> const std::vector<WhetherForecast>&
	{
		return _vector;
	}
}
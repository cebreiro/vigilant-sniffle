/**********************************************************
         AUTO GENERATED FILE BY sox_code_generator
                   DO NOT EDIT THIS FILE
**********************************************************/
#include "pet_conversion.h"

#include "lib/common/stream/stream_reader.h"
#include "lib/game_base/data/sox/sox_file.h"
#include "lib/game_data/game_data_registry.h"

namespace cebreiro::gamedata
{
	[[maybe_unused]]
	static GameDataRegistry<PetConversionTable> registry;

	PetConversion::PetConversion(StreamReader& reader)
	{
		index = reader.ReadInt32();
		maxSt = reader.ReadInt32();
		exp = reader.ReadInt32();
		stInc = reader.ReadInt32();
		npDec = reader.ReadFloat32();
		expDecNp0 = reader.ReadInt32();
		freqIdleMotion = reader.ReadFloat32();
		moveSpeed = reader.ReadInt32();
		caressCount = reader.ReadFloat32();
		caressExp = reader.ReadInt32();
		annoyCount = reader.ReadFloat32();
		annoyExpInc = reader.ReadInt32();
		annoyExpDec = reader.ReadInt32();
		abFetchScanRange = reader.ReadInt32();
		abFetchScanFreq = reader.ReadFloat32();
		abFetchNoItem = reader.ReadInt32();
		abAttackAttackPower = reader.ReadInt32();
		abAttackScanRange = reader.ReadInt32();
		abAttackScanFreq = reader.ReadFloat32();
	}

	void PetConversionTable::LoadFromFile(const std::filesystem::path& path)
	{
		gamebase::SoxFile fileData(path / "PET_CONVERSION.sox");
		StreamReader reader(fileData.gameData.data(), fileData.gameData.size());

		_vector.reserve(fileData.rowCount);
		for (int32_t i = 0; i < fileData.rowCount; ++i)
		{
			_vector.emplace_back(reader);
		}

		for (const PetConversion& data : _vector)
		{
			_umap[data.index] = &data;
		}
	}

	auto PetConversionTable::Find(int32_t index) const -> const PetConversion*
	{
		auto iter = _umap.find(index);
		return iter != _umap.end() ? iter->second : nullptr;
	}

	auto PetConversionTable::Get() const -> const std::vector<PetConversion>&
	{
		return _vector;
	}
}

/**********************************************************
         AUTO GENERATED FILE BY sox_code_generator
                   DO NOT EDIT THIS FILE
**********************************************************/
#include "damage_sound.h"

#include "lib/common/stream/stream_reader.h"
#include "lib/game_base/data/sox/sox_file.h"
#include "lib/game_data/game_data_registry.h"

namespace cebreiro::gamedata
{
	[[maybe_unused]]
	static GameDataRegistry<DamageSoundTable> registry;

	DamageSound::DamageSound(StreamReader& reader)
	{
		index = reader.ReadInt32();
		matHard = reader.ReadInt32();
		matNormal = reader.ReadInt32();
		matSoft = reader.ReadInt32();
		matReserved1 = reader.ReadInt32();
		matReserved2 = reader.ReadInt32();
		matReserved3 = reader.ReadInt32();
	}

	void DamageSoundTable::LoadFromFile(const std::filesystem::path& path)
	{
		gamebase::SoxFile fileData(path / "DAMAGE_SOUND.sox");
		StreamReader reader(fileData.gameData.data(), fileData.gameData.size());

		_vector.reserve(fileData.rowCount);
		for (int32_t i = 0; i < fileData.rowCount; ++i)
		{
			_vector.emplace_back(reader);
		}

		for (const DamageSound& data : _vector)
		{
			_umap[data.index] = &data;
		}
	}

	auto DamageSoundTable::Find(int32_t index) const -> const DamageSound*
	{
		auto iter = _umap.find(index);
		return iter != _umap.end() ? iter->second : nullptr;
	}

	auto DamageSoundTable::Get() const -> const std::vector<DamageSound>&
	{
		return _vector;
	}
}

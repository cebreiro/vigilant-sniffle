/**********************************************************
         AUTO GENERATED FILE BY sox_code_generator
                   DO NOT EDIT THIS FILE
**********************************************************/
#include "item_etc.h"

#include "lib/common/stream/stream_reader.h"
#include "lib/game_base/data/sox/sox_file.h"
#include "lib/game_data/game_data_registry.h"

namespace cebreiro::gamedata
{
	[[maybe_unused]]
	static GameDataRegistry<ItemEtcTable> registry;

	ItemEtc::ItemEtc(StreamReader& reader)
	{
		index = reader.ReadInt32();
		name = reader.ReadString(reader.ReadUInt16());
		generate = reader.ReadInt32();
		explanation = reader.ReadString(reader.ReadUInt16());
		invenWidth = reader.ReadInt32();
		invenHeight = reader.ReadInt32();
		maxOverlapCount = reader.ReadInt32();
		rarity = reader.ReadInt32();
		price = reader.ReadInt32();
		modelID = reader.ReadInt32();
		modelColor = reader.ReadInt32();
		dropSound = reader.ReadInt32();
		useQuickSlot = reader.ReadInt32();
		oneMoreItem = reader.ReadInt32();
		equipPos = reader.ReadInt32();
		money = reader.ReadInt32();
		bulletType = reader.ReadInt32();
		ableToSell = reader.ReadInt32();
		ableToTrade = reader.ReadInt32();
		ableToDrop = reader.ReadInt32();
		ableToDestroy = reader.ReadInt32();
		ableToStorage = reader.ReadInt32();
		skillID = reader.ReadInt32();
		grade = reader.ReadInt32();
		isTool = reader.ReadInt32();
		mixDistance = reader.ReadInt32();
		interfaceAniID = reader.ReadInt32();
		toolMotionID = reader.ReadInt32();
		charMotionLoopID = reader.ReadInt32();
		charMotionStartID = reader.ReadInt32();
		toolSoundID = reader.ReadInt32();
		toolEventSoundID = reader.ReadInt32();
	}

	void ItemEtcTable::LoadFromFile(const std::filesystem::path& path)
	{
		gamebase::SoxFile fileData(path / "item_etc.sox");
		StreamReader reader(fileData.gameData.data(), fileData.gameData.size());

		_vector.reserve(fileData.rowCount);
		for (int32_t i = 0; i < fileData.rowCount; ++i)
		{
			_vector.emplace_back(reader);
		}

		for (const ItemEtc& data : _vector)
		{
			_umap[data.index] = &data;
		}
	}

	auto ItemEtcTable::Find(int32_t index) const -> const ItemEtc*
	{
		auto iter = _umap.find(index);
		return iter != _umap.end() ? iter->second : nullptr;
	}

	auto ItemEtcTable::Get() const -> const std::vector<ItemEtc>&
	{
		return _vector;
	}
}

/**********************************************************
         AUTO GENERATED FILE BY sox_code_generator
                   DO NOT EDIT THIS FILE
**********************************************************/
#pragma once
#include <cstdint>
#include <string>
#include <vector>
#include <unordered_map>
#include <filesystem>
#include "lib/game_data/game_data_table.h"

namespace cebreiro { class StreamReader; }

namespace cebreiro::gamedata
{
	struct ItemEtc
	{
		ItemEtc() = default;
		explicit ItemEtc(StreamReader& reader);

		int32_t index = 0;
		std::string name;
		int32_t generate = 0;
		std::string explanation;
		int32_t invenWidth = 0;
		int32_t invenHeight = 0;
		int32_t maxOverlapCount = 0;
		int32_t rarity = 0;
		int32_t price = 0;
		int32_t modelID = 0;
		int32_t modelColor = 0;
		int32_t dropSound = 0;
		int32_t useQuickSlot = 0;
		int32_t oneMoreItem = 0;
		int32_t equipPos = 0;
		int32_t money = 0;
		int32_t bulletType = 0;
		int32_t ableToSell = 0;
		int32_t ableToTrade = 0;
		int32_t ableToDrop = 0;
		int32_t ableToDestroy = 0;
		int32_t ableToStorage = 0;
		int32_t skillID = 0;
		int32_t grade = 0;
		int32_t isTool = 0;
		int32_t mixDistance = 0;
		int32_t interfaceAniID = 0;
		int32_t toolMotionID = 0;
		int32_t charMotionLoopID = 0;
		int32_t charMotionStartID = 0;
		int32_t toolSoundID = 0;
		int32_t toolEventSoundID = 0;
	};

	class ItemEtcTable : public GameDataTable
	{
	public:
		 static constexpr int64_t INDEX = 30;

	public:
		void LoadFromFile(const std::filesystem::path& path);

		auto Find(int32_t index) const -> const ItemEtc*;
		auto Get() const -> const std::vector<ItemEtc>&;

	private:
		std::vector<ItemEtc> _vector;
		std::unordered_map<int32_t, const ItemEtc*> _umap;
	};
}

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
	struct PetMotion
	{
		PetMotion() = default;
		explicit PetMotion(StreamReader& reader);

		int32_t index = 0;
		std::string name;
		int32_t modelId = 0;
		int32_t generateFrame = 0;
		int32_t lovelyFrame = 0;
		int32_t afflictFrame = 0;
		int32_t eatFrame = 0;
		int32_t eatTiming = 0;
		int32_t hungryFrame = 0;
		int32_t idle01Frame = 0;
		int32_t idle02Frame = 0;
		int32_t idle03Frame = 0;
		int32_t idle04Frame = 0;
		int32_t idle05Frame = 0;
		int32_t attackFrame = 0;
		int32_t attackTiming = 0;
		int32_t pickupFrame = 0;
		int32_t pickupTiming = 0;
	};

	class PetMotionTable : public GameDataTable
	{
	public:
		 static constexpr int64_t INDEX = 65;

	public:
		void LoadFromFile(const std::filesystem::path& path);

		auto Find(int32_t index) const -> const PetMotion*;
		auto Get() const -> const std::vector<PetMotion>&;

	private:
		std::vector<PetMotion> _vector;
		std::unordered_map<int32_t, const PetMotion*> _umap;
	};
}
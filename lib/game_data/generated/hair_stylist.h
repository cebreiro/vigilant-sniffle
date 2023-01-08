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
	struct HairStylist
	{
		HairStylist() = default;
		explicit HairStylist(StreamReader& reader);

		int32_t index = 0;
		int32_t coloringPrice = 0;
		int32_t id01 = 0;
		int32_t sex01 = 0;
		int32_t price01 = 0;
		int32_t id02 = 0;
		int32_t sex02 = 0;
		int32_t price02 = 0;
		int32_t id03 = 0;
		int32_t sex03 = 0;
		int32_t price03 = 0;
		int32_t id04 = 0;
		int32_t sex04 = 0;
		int32_t price04 = 0;
		int32_t id05 = 0;
		int32_t sex05 = 0;
		int32_t price05 = 0;
		int32_t id06 = 0;
		int32_t sex06 = 0;
		int32_t price06 = 0;
		int32_t id07 = 0;
		int32_t sex07 = 0;
		int32_t price07 = 0;
		int32_t id08 = 0;
		int32_t sex08 = 0;
		int32_t price08 = 0;
		int32_t id09 = 0;
		int32_t sex09 = 0;
		int32_t price09 = 0;
		int32_t id10 = 0;
		int32_t sex10 = 0;
		int32_t price10 = 0;
		int32_t id11 = 0;
		int32_t sex11 = 0;
		int32_t price11 = 0;
		int32_t id12 = 0;
		int32_t sex12 = 0;
		int32_t price12 = 0;
		int32_t id13 = 0;
		int32_t sex13 = 0;
		int32_t price13 = 0;
		int32_t id14 = 0;
		int32_t sex14 = 0;
		int32_t price14 = 0;
		int32_t id15 = 0;
		int32_t sex15 = 0;
		int32_t price15 = 0;
		int32_t id16 = 0;
		int32_t sex16 = 0;
		int32_t price16 = 0;
		int32_t id17 = 0;
		int32_t sex17 = 0;
		int32_t price17 = 0;
		int32_t id18 = 0;
		int32_t sex18 = 0;
		int32_t price18 = 0;
		int32_t id19 = 0;
		int32_t sex19 = 0;
		int32_t price19 = 0;
		int32_t id20 = 0;
		int32_t sex20 = 0;
		int32_t price20 = 0;
		int32_t id21 = 0;
		int32_t sex21 = 0;
		int32_t price21 = 0;
		int32_t id22 = 0;
		int32_t sex22 = 0;
		int32_t price22 = 0;
		int32_t id23 = 0;
		int32_t sex23 = 0;
		int32_t price23 = 0;
		int32_t id24 = 0;
		int32_t sex24 = 0;
		int32_t price24 = 0;
		int32_t id25 = 0;
		int32_t sex25 = 0;
		int32_t price25 = 0;
		int32_t id26 = 0;
		int32_t sex26 = 0;
		int32_t price26 = 0;
		int32_t id27 = 0;
		int32_t sex27 = 0;
		int32_t price27 = 0;
		int32_t id28 = 0;
		int32_t sex28 = 0;
		int32_t price28 = 0;
		int32_t id29 = 0;
		int32_t sex29 = 0;
		int32_t price29 = 0;
		int32_t id30 = 0;
		int32_t sex30 = 0;
		int32_t price30 = 0;
		int32_t id31 = 0;
		int32_t sex31 = 0;
		int32_t price31 = 0;
		int32_t id32 = 0;
		int32_t sex32 = 0;
		int32_t price32 = 0;
		int32_t id33 = 0;
		int32_t sex33 = 0;
		int32_t price33 = 0;
		int32_t id34 = 0;
		int32_t sex34 = 0;
		int32_t price34 = 0;
		int32_t id35 = 0;
		int32_t sex35 = 0;
		int32_t price35 = 0;
		int32_t id36 = 0;
		int32_t sex36 = 0;
		int32_t price36 = 0;
		int32_t id37 = 0;
		int32_t sex37 = 0;
		int32_t price37 = 0;
		int32_t id38 = 0;
		int32_t sex38 = 0;
		int32_t price38 = 0;
		int32_t id39 = 0;
		int32_t sex39 = 0;
		int32_t price39 = 0;
		int32_t id40 = 0;
		int32_t sex40 = 0;
		int32_t price40 = 0;
	};

	class HairStylistTable : public GameDataTable
	{
	public:
		 static constexpr int64_t INDEX = 16;

	public:
		void LoadFromFile(const std::filesystem::path& path);

		auto Find(int32_t index) const -> const HairStylist*;
		auto Get() const -> const std::vector<HairStylist>&;

	private:
		std::vector<HairStylist> _vector;
		std::unordered_map<int32_t, const HairStylist*> _umap;
	};
}
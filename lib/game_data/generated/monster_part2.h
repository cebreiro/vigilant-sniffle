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
	struct MonsterPart2
	{
		MonsterPart2() = default;
		explicit MonsterPart2(StreamReader& reader);

		int32_t index = 0;
		int32_t attack1type = 0;
		float attack1percent = 0.f;
		int32_t attack1range = 0;
		float attack1dmgfactor = 0.f;
		int32_t attack1effectrange = 0;
		int32_t attack1additional = 0;
		int32_t attack1reserved1 = 0;
		int32_t attack1reserved2 = 0;
		int32_t attack1reserved3 = 0;
		int32_t attack1fx = 0;
		int32_t attack1abnormality = 0;
		int32_t attack1abnormalityDuration = 0;
		int32_t attack1abnormalityProbmod = 0;
		int32_t attack1abnormalityReserved1 = 0;
		int32_t attack1abnormalityReserved2 = 0;
		int32_t attack1atkanipartid = 0;
		int32_t attack1atkprm = 0;
		int32_t attack1delay = 0;
		int32_t attack1beatkani = 0;
		int32_t attack1FxType = 0;
		int32_t attack1FxId = 0;
		int32_t attack1Sound = 0;
		int32_t attack2type = 0;
		float attack2percent = 0.f;
		int32_t attack2range = 0;
		float attack2dmgfactor = 0.f;
		int32_t attack2effectrange = 0;
		int32_t attack2additional = 0;
		int32_t attack2reserved1 = 0;
		int32_t attack2reserved2 = 0;
		int32_t attack2reserved3 = 0;
		int32_t attack2fx = 0;
		int32_t attack2abnormality = 0;
		int32_t attack2abnormalityDuration = 0;
		int32_t attack2abnormalityProbmod = 0;
		int32_t attack2abnormalityReserved1 = 0;
		int32_t attack2abnormalityReserved2 = 0;
		int32_t attack2atkanipartid = 0;
		int32_t attack2atkprm = 0;
		int32_t attack2delay = 0;
		int32_t attack2beatkani = 0;
		int32_t attack2FxType = 0;
		int32_t attack2FxId = 0;
		int32_t attack2Sound = 0;
		int32_t attack3type = 0;
		float attack3percent = 0.f;
		int32_t attack3range = 0;
		float attack3dmgfactor = 0.f;
		int32_t attack3effectrange = 0;
		int32_t attack3additional = 0;
		int32_t attack3reserved1 = 0;
		int32_t attack3reserved2 = 0;
		int32_t attack3reserved3 = 0;
		int32_t attack3fx = 0;
		int32_t attack3abnormality = 0;
		int32_t attack3abnormalityDuration = 0;
		int32_t attack3abnormalityProbmod = 0;
		int32_t attack3abnormalityReserved1 = 0;
		int32_t attack3abnormalityReserved3 = 0;
		int32_t attack3atkanipartid = 0;
		int32_t attack3atkprm = 0;
		int32_t attack3delay = 0;
		int32_t attack3beatkani = 0;
		int32_t attack3FxType = 0;
		int32_t attack3FxId = 0;
		int32_t attack3Sound = 0;
		int32_t attack4type = 0;
		float attack4percent = 0.f;
		int32_t attack4range = 0;
		float attack4dmgfactor = 0.f;
		int32_t attack4effectrange = 0;
		int32_t attack4additional = 0;
		int32_t attack4reserved1 = 0;
		int32_t attack4reserved2 = 0;
		int32_t attack4reserved3 = 0;
		int32_t attack4fx = 0;
		int32_t attack4abnormality = 0;
		int32_t attack4abnormalityDuration = 0;
		int32_t attack4abnormalityProbmod = 0;
		int32_t attack4abnormalityReserved1 = 0;
		int32_t attack4abnormalityReserved4 = 0;
		int32_t attack4atkanipartid = 0;
		int32_t attack4atkprm = 0;
		int32_t attack4delay = 0;
		int32_t attack4beatkani = 0;
		int32_t attack4FxType = 0;
		int32_t attack4FxId = 0;
		int32_t attack4Sound = 0;
	};

	class MonsterPart2Table : public GameDataTable
	{
	public:
		 static constexpr int64_t INDEX = 59;

	public:
		void LoadFromFile(const std::filesystem::path& path);

		auto Find(int32_t index) const -> const MonsterPart2*;
		auto Get() const -> const std::vector<MonsterPart2>&;

	private:
		std::vector<MonsterPart2> _vector;
		std::unordered_map<int32_t, const MonsterPart2*> _umap;
	};
}
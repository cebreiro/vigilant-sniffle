/**********************************************************
         AUTO GENERATED FILE BY sox_code_generator
                   DO NOT EDIT THIS FILE
**********************************************************/
#include "ability_client.h"

#include "lib/common/stream/stream_reader.h"
#include "lib/game_base/data/sox/sox_file.h"
#include "lib/game_data/game_data_registry.h"

namespace cebreiro::gamedata
{
	[[maybe_unused]]
	static GameDataRegistry<AbilityClientTable> registry;

	AbilityClient::AbilityClient(StreamReader& reader)
	{
		index = reader.ReadInt32();
		abilityName = reader.ReadString(reader.ReadUInt16());
		abilityRoutine = reader.ReadInt32();
		totalTime = reader.ReadInt32();
		_1Hand00Pid = reader.ReadInt32();
		_2Hand00Pid = reader.ReadInt32();
		spearPid = reader.ReadInt32();
		polearmPid = reader.ReadInt32();
		glovePid = reader.ReadInt32();
		bowPid = reader.ReadInt32();
		handgunPid = reader.ReadInt32();
		doublegunPid = reader.ReadInt32();
		shotgunPid = reader.ReadInt32();
		throwPid = reader.ReadInt32();
		_1Hand00StartDamageFrame = reader.ReadInt32();
		_2Hand00StartDamageFrame = reader.ReadInt32();
		spearStartDamageFrame = reader.ReadInt32();
		polearmDamageFrame = reader.ReadInt32();
		gloveStartDamageFrame = reader.ReadInt32();
		bowStartDamageFrame = reader.ReadInt32();
		handgunStartDamageFrame = reader.ReadInt32();
		doublegunStartDamageFrame = reader.ReadInt32();
		shotgunStartDamageFrame = reader.ReadInt32();
		throwStartDamageFrame = reader.ReadInt32();
		_1Hand00Timing = reader.ReadInt32();
		_2Hand00Timing = reader.ReadInt32();
		spearTiming = reader.ReadInt32();
		polearmTiming = reader.ReadInt32();
		gloveTiming = reader.ReadInt32();
		bowTiming = reader.ReadInt32();
		handgunTiming = reader.ReadInt32();
		doublegunTiming = reader.ReadInt32();
		shotgunTiming = reader.ReadInt32();
		throwTiming = reader.ReadInt32();
		_1Hand00FullTime = reader.ReadInt32();
		_2Hand00FullTime = reader.ReadInt32();
		spearFullTime = reader.ReadInt32();
		polearmFullTime = reader.ReadInt32();
		gloveFullTime = reader.ReadInt32();
		bowFullTime = reader.ReadInt32();
		handgunFullTime = reader.ReadInt32();
		doublegunFullTime = reader.ReadInt32();
		shotgunFullTime = reader.ReadInt32();
		throwFullTime = reader.ReadInt32();
		isUniqueItemAbility = reader.ReadInt32();
		uniqueItemAbilityPid = reader.ReadInt32();
		chargeFXGid = reader.ReadInt32();
		chargeFXPid = reader.ReadInt32();
		defaultShockFX = reader.ReadInt32();
		shockFXGid = reader.ReadInt32();
		shockFXPid = reader.ReadInt32();
		abilityDelay = reader.ReadInt32();
		locationTab = reader.ReadInt32();
		locationX = reader.ReadInt32();
		locationY = reader.ReadInt32();
		detail = reader.ReadString(reader.ReadUInt16());
		iconTextureId = reader.ReadInt32();
		iconLocation = reader.ReadInt32();
		iconTexture2Id = reader.ReadInt32();
		iconLocation2 = reader.ReadInt32();
		reserved1 = reader.ReadInt32();
		reserved2 = reader.ReadInt32();
		dmgPenalty = reader.ReadFloat32();
		category = reader.ReadInt32();
		cancelable = reader.ReadInt32();
		five = reader.ReadInt32();
		spendSP = reader.ReadInt32();
		length = reader.ReadInt32();
		keepTime = reader.ReadInt32();
		damageLength = reader.ReadInt32();
		usage = reader.ReadInt32();
		applyTarget = reader.ReadInt32();
		addWeaponRange = reader.ReadInt32();
		damageStyle = reader.ReadInt32();
		damageReserved1 = reader.ReadInt32();
		damageReserved2 = reader.ReadInt32();
		damageMotionType = reader.ReadInt32();
		sideEffect1 = reader.ReadInt32();
		sideEffect2 = reader.ReadInt32();
		statusValType1 = reader.ReadInt32();
		statusValType2 = reader.ReadInt32();
		statusProb = reader.ReadInt32();
		statusReserved11 = reader.ReadInt32();
		statusReserved12 = reader.ReadInt32();
		statusReserved21 = reader.ReadInt32();
		statusReserved22 = reader.ReadInt32();
		job = reader.ReadInt32();
		exp = reader.ReadInt32();
		speed = reader.ReadFloat32();
		requireItem = reader.ReadInt32();
		spendItem = reader.ReadInt32();
		spendBullet = reader.ReadInt32();
		increaseHit = reader.ReadInt32();
		needWeapon = reader.ReadInt32();
	}

	void AbilityClientTable::LoadFromFile(const std::filesystem::path& path)
	{
		gamebase::SoxFile fileData(path / "ABILITY_CLIENT.sox");
		StreamReader reader(fileData.gameData.data(), fileData.gameData.size());

		_vector.reserve(fileData.rowCount);
		for (int32_t i = 0; i < fileData.rowCount; ++i)
		{
			_vector.emplace_back(reader);
		}

		for (const AbilityClient& data : _vector)
		{
			_umap[data.index] = &data;
		}
	}

	auto AbilityClientTable::Find(int32_t index) const -> const AbilityClient*
	{
		auto iter = _umap.find(index);
		return iter != _umap.end() ? iter->second : nullptr;
	}

	auto AbilityClientTable::Get() const -> const std::vector<AbilityClient>&
	{
		return _vector;
	}
}

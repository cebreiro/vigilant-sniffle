#include "player_appearance_component.h"

#include "lib/game_base/db/character.h"

namespace cebreiro::zone
{
	PlayerAppearanceComponent::PlayerAppearanceComponent(GameObject& object, const gamebase::Character& character)
		: ComponentBase(object)
		, _hair(character.hair)
		, _hairColor(character.hair_color)
		, _face(character.face)
		, _skinColor(character.skin_color)
	{
		SetDoTick(false);
	}

	auto PlayerAppearanceComponent::GetHair() const -> int32_t
	{
		return _hair;
	}

	auto PlayerAppearanceComponent::GetHairColor() const -> int32_t
	{
		return _hairColor;
	}

	auto PlayerAppearanceComponent::GetFace() const -> int32_t
	{
		return _face;
	}

	auto PlayerAppearanceComponent::GetSkinColor() const -> int32_t
	{
		return _skinColor;
	}

	void PlayerAppearanceComponent::SetHair(int32_t hair)
	{
		_hair = hair;
	}

	void PlayerAppearanceComponent::SetHairColor(int32_t hairColor)
	{
		_hairColor = hairColor;
	}

	void PlayerAppearanceComponent::SetFace(int32_t face)
	{
		_face = face;
	}

	void PlayerAppearanceComponent::SetSkinColor(int32_t skinColor)
	{
		_skinColor = skinColor;
	}
}

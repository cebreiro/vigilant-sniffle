#pragma once
#include "zone/game/component/component_base.h"

namespace cebreiro::gamebase
{
	struct Character;
}

namespace cebreiro::zone
{
	class PlayerAppearanceComponent : public ComponentBase
	{
	public:
		PlayerAppearanceComponent(GameObject& object, const gamebase::Character& character);

		auto GetHair() const -> int32_t;
		auto GetHairColor() const -> int32_t;
		auto GetFace() const -> int32_t;
		auto GetSkinColor() const -> int32_t;

		void SetHair(int32_t hair);
		void SetHairColor(int32_t hairColor);
		void SetFace(int32_t face);
		void SetSkinColor(int32_t skinColor);

	private:
		int32_t _hair = 0;
		int32_t _hairColor = 0;
		int32_t _face = 0;
		int32_t _skinColor = 0;
	};
}
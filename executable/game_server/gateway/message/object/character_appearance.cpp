#include "character_appearance.h"

#include "lib/game_base/db/character.h"
#include "lib/game_base/type/equip_position.h"
#include "lib/game_data/game_data_source.h"
#include "lib/game_data/generated/item_clothes.h"
#include "lib/game_db/entity/character.h"

namespace cebreiro::gateway
{
	namespace
	{
		auto FindItem(const std::vector<gamebase::CharacterItem>& items, type::EquipPosition equipPosition)
			-> const gamebase::CharacterItem*
		{
			auto iter = sr::find_if(items, [equipPosition](const gamebase::CharacterItem& item)
				{
					return item.equip_position == static_cast<int8_t>(equipPosition);
				});
			return iter != items.end() ? &(*iter) : nullptr;
		}

		auto FindItemIdOrDefault(const std::vector<gamebase::CharacterItem>& items, type::EquipPosition equipPosition, int32_t defaultValue = 0)
			-> int32_t
		{
			const gamebase::CharacterItem* item = FindItem(items, equipPosition);
			return item ? item->item_id : defaultValue;
		}
	}

	CharacterAppearance::CharacterAppearance(const gamedata::GameDataSource& dataSource,
		const gamedb::Character& character)
		: _hatModelId([&]() -> std::optional<int32_t>
			{
				const gamebase::CharacterItem* item = FindItem(character.items, type::EquipPosition::Hat);
				if (item)
				{
					const auto& data = dataSource.Get<gamedata::ItemClothesTable>()->Find(item->item_id);
					if (data)
					{
						return data->modelID;
					}
				}

				return std::nullopt;
			}())
		, _hairModel(character.base.hair)
		, _hairColor(character.base.hair_color)
		, _skinColor(character.base.skin_color)
		, _face(character.base.face)
		, _jacketId(FindItemIdOrDefault(character.items, type::EquipPosition::Jacket))
		, _glovesModelId([&]() -> int32_t
			{
				const gamebase::CharacterItem* item = FindItem(character.items, type::EquipPosition::Gloves);
				if (item)
				{
					const auto& data = dataSource.Get<gamedata::ItemClothesTable>()->Find(item->item_id);
					if (data)
					{
						return data->modelID;
					}
				}

				return 0;
			}())
		, _pantsId(FindItemIdOrDefault(character.items, type::EquipPosition::Pants))
		, _shoesId(FindItemIdOrDefault(character.items, type::EquipPosition::Shoes))
	{
	}

	auto CharacterAppearance::Serialize() const -> gamebase::SerializedObject
	{
		gamebase::SerializedObject object;

		object.WriteInt32(_hatModelId.has_value() ? _hairModel : 0);
		object.WriteInt32(_hairColor);
		object.WriteInt32(_skinColor);
		object.WriteInt32(_face);
		object.WriteInt32(0);
		object.WriteInt32(0);
		object.WriteInt32(_hatModelId.has_value() ? _hatModelId.value() : _hairModel);
		object.WriteInt32(0);
		object.WriteInt32(0); // hat

		object.WriteInt32(_jacketId); // itemid
		object.WriteInt32(0);
		object.WriteInt32(0);

		object.WriteInt32(_glovesModelId);
		object.WriteInt32(0);
		object.WriteInt32(0);

		object.WriteInt32(_pantsId);
		object.WriteInt32(0);
		object.WriteInt32(0);

		object.WriteInt32(_shoesId);
		object.WriteInt32(0);
		object.WriteInt32(0);

		object.WriteInt32(0); // ½æ¶ò
		object.WriteInt32(0);
		object.WriteInt32(0);

		return object;
	}
}

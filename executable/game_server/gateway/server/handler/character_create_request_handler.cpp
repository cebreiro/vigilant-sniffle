#include "character_create_request_handler.h"

#include "gateway/message/sc/character_create_response.h"
#include "lib/common/log/log_macro.h"
#include "lib/common/execution/future_await.h"
#include "lib/network/session.h"
#include "gateway/server/gateway_session_context.h"
#include "gateway/server/handler/cs_message_handler_auto_registry.h"
#include "lib/game_base/type/equip_position.h"
#include "lib/game_data/game_data_source.h"
#include "lib/game_data/generated/skill_basic.h"
#include "service/service_locator.h"

namespace cebreiro::gateway
{
	[[maybe_unused]]
	static CSMessageHandlerAutoRegistryT<CharacterCreateRequestHandler> registry;

	auto CharacterCreateRequestHandler::OnMessage(const IServiceLocator& locator, GatewaySessionContext& context,
		const CharacterCreateRequest& message) -> Future<void>
	{
		network::Session& session = *context.session;

		if (context.state != GatewaySessionState::Authorized)
		{
			OnError(locator, context,
				std::format("invalid request. state: {}, session: {}",
					static_cast<int32_t>(context.state), session.Id().Value(), session.RemoteAddress()));
			co_return;
		}

		if (!message.IsValid(locator.GameDataSource()))
		{
			OnError(locator, context, 
				std::format("CharacterCreateRequest message is invalid. session:[{}:{}]",
					session.Id().Value(), session.RemoteAddress()));

			co_return;
		}

		for (const gamedb::Character& character : context.characters)
		{
			if (character.base.slot == message.slot)
			{
				OnError(locator, context, 
					std::format("duplicated character slot error. cid: {}, slot: {}, session:[{}:{}]",
						character.base.id, message.slot, session.Id().Value(), session.RemoteAddress()));
				co_return;
			}
		}

		bool result = co_await locator.WorldService(context.worldId).CreateCharacter(co_await CreateCharacter(locator, context, message))
			.ConfigureAwait(context.strand);

		if (result)
		{
			context.characters.clear();
			context.characters = co_await locator.WorldService(context.worldId).GetCharacters(context.accountId)
				.ConfigureAwait(context.strand);

			context.session->Send(CharacterCreateResponse(true).Serialize());
		}
		else
		{
			OnError(locator, context,
				std::format("fail to create character - db error. slot: {}, session:[{}:{}]",
					message.slot, session.Id().Value(), session.RemoteAddress()));
		}
	}

	void CharacterCreateRequestHandler::OnError(const IServiceLocator& locator, const GatewaySessionContext& context, std::string log)
	{
		LOGE(locator.LogService(), std::move(log));

		context.session->Send(CharacterCreateResponse(false).Serialize());
	}

	auto CharacterCreateRequestHandler::CreateCharacter(const IServiceLocator& locator,
		const GatewaySessionContext& context, const CharacterCreateRequest& message) const -> Future<gamedb::Character>
	{
		auto future1 = locator.WorldService(context.worldId).GenerateCharacterId();
		auto future2 = locator.WorldService(context.worldId).GenerateCharacterId();
		auto future3 = locator.WorldService(context.worldId).GenerateCharacterId();
		auto future4 = locator.WorldService(context.worldId).GenerateCharacterId();

		co_await WaitAll(future1, future2, future3, future4);

		int64_t cid = future1.Get();
		int64_t itemId1 = future2.Get();
		int64_t itemId2 = future3.Get();
		int64_t itemId3 = future4.Get();

		auto createItem = [](int64_t id, int64_t cid, int32_t itemId, int8_t equipPosition)
		{
			return gamebase::CharacterItem{
				.id = id,
				.cid = cid,
				.item_id = itemId,
				.quantity = 1,
				.equip_position = equipPosition,
				.page = -1,
				.x = -1,
				.y = -1,
				.is_in_quick = false,
				.is_pick = false,
			};
		};

		auto skillView = locator.GameDataSource().Get<gamedata::SkillBasicTable>()->Get()
		| srv::filter([&](const gamedata::SkillBasic& data)
			{
				return data.job1 == message.job1 && data.levelQualification <= 1;
			})
		| srv::transform([&](const gamedata::SkillBasic& data) -> gamebase::CharacterSkill
			{
				return gamebase::CharacterSkill{
					.cid = cid,
					.skill_id = data.index,
					.job = message.job1,
					.level = 1,
					.cooldown = 0,
					.page = -1,
					.x = -1,
					.y = -1,
					.is_in_quick = false
				};
			});

		co_return gamedb::Character{
			.base = gamebase::Character{
				.id = cid,
				.aid = context.accountId,
				.wid = context.worldId,
				.slot = message.slot,
				.name = message.name,
				.hair_color = message.hairColor,
				.hair = message.hair,
				.skin_color = message.skinColor,
				.face = message.face,
				.arms = false,
				.running = false,
				.gold = 500,
				.inventory_page = 1,
				.zone = 401,
				.stage = 10000,
				.x = 9685.f,
				.y = 8652.f,
			},
			.stat = gamebase::CharacterStat{
				.cid = cid,
				.gender = message.gender,
				.hp = 100000,
				.mp = 100000,
				.chr_lv = 1,
				.chr_exp = 0,
				.str = message.str,
				.dex = message.dex,
				.accr = message.accr,
				.health = message.health,
				.intell = message.intell,
				.wis = message.wis,
				.will = message.will,
				.stat_point = message.unk01,
				.water = message.water,
				.fire = message.fire,
				.lightning = message.lightning
			},
			.job = gamebase::CharacterJob{
				.cid = cid,
				.job1 = message.job1,
				.job1_level = 0,
			},
			.items = {
				createItem(itemId1, cid, message.jacketId, static_cast<int8_t>(type::EquipPosition::Jacket)),
				createItem(itemId2, cid, message.pantsId, static_cast<int8_t>(type::EquipPosition::Pants)),
				createItem(itemId3, cid, message.shoesId, static_cast<int8_t>(type::EquipPosition::Shoes)),
			},
			.skills = std::vector(skillView.begin(), skillView.end()),
		};
	}
}

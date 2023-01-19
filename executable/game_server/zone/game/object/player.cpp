#include "player.h"

#include "lib/game_db/entity/character.h"
#include "zone/game/zone.h"
#include "zone/game/component/movement_component.h"
#include "zone/game/component/player_appearance_component.h"
#include "zone/game/component/player_job_component.h"
#include "zone/game/component/player_stat_component.h"
#include "zone/game/controller/player/remote_player_controller.h"
#include "zone/game/domain/job/player_job.h"
#include "zone/message/object/movement.h"

namespace cebreiro::zone
{
	Player::Player(Zone& zone, GameObjectId id, const gamedb::Character& character, std::shared_ptr<network::Session> session)
		: GameObject(zone, id)
	{
		SetController(std::make_shared<RemotePlayerController>(std::move(session)));

		[[maybe_unused]] bool result = false;

		Movement movement = {};
		movement.position = Vector3D(character.base.x, character.base.y, 0.f);
		movement.destPosition = movement.position;
		movement.direction = 90.f;

		result = Add(std::make_shared<MovementComponent>(*this, zone.CreateMoverId(), movement));
		assert(result);

		result = Add(std::make_shared<PlayerAppearanceComponent>(*this, character.base));
		assert(result);

		result = Add(std::make_shared<PlayerStatComponent>(*this, character.stat));
		assert(result);

		result = Add(std::make_shared<PlayerJobComponent>(*this, character.job));
		assert(result);
	}

	Player::~Player()
	{
	}
}

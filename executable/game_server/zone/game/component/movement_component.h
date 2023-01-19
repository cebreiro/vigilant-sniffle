#pragma once
#include "lib/common/time_util.h"
#include "zone/game/component/component_base.h"
#include "zone/message/object/movement.h"

namespace cebreiro::zone
{
	class MovementComponent : public ComponentBase
	{
	public:
		MovementComponent(GameObject& object, int32_t moverId, const Movement& movement);

		void MoveTo(const Vector3D& destination);

		bool IsMoving() const;

		auto GetMoverId() const -> int32_t;
		auto GetMovement() const -> const Movement&;
		auto GetPosition() const -> const Vector3D&;
		auto GetDestination() const -> const Vector3D&;
		auto GetSpeed() const -> float;

		void SetMovement(const Movement& movement);
		void SetPosition(const Vector3D& position);
		void SetDestination(const Vector3D& position);
		void SetDirection(float value);
		void SetSpeed(float value);
		void SetMoving(bool value);

	private:
		void OnTick(time_point_t now) override;

	private:
		int32_t _moverId = -1;
		Movement _movement = {};
		Vector3D _startPosition = {};
		Vector3D _dist = {};
		float _time = 0.f;
		time_point_t _lastMovementTimePoint;
	};
}

#include "movement_component.h"

#include "lib/common/math/math_util.h"

namespace cebreiro::zone
{
	MovementComponent::MovementComponent(GameObject& object, int32_t moverId, const Movement& movement)
		: ComponentBase(object)
		, _moverId(moverId)
		, _movement(movement)
		, _startPosition(movement.position)
	{
	}

	void MovementComponent::MoveTo(const Vector3D& destination)
	{
		_movement.destPosition = destination;
		_movement.SetMoving(true);

		_startPosition = _movement.position;
		_lastMovementTimePoint = clock_t::now();
	}

	bool MovementComponent::IsMoving() const
	{
		return _movement.IsMoving();
	}

	auto MovementComponent::GetMoverId() const -> int32_t
	{
		return _moverId;
	}

	auto MovementComponent::GetMovement() const -> const Movement&
	{
		return _movement;
	}

	auto MovementComponent::GetPosition() const -> const Vector3D&
	{
		return _movement.position;
	}

	auto MovementComponent::GetDestination() const -> const Vector3D&
	{
		return _movement.destPosition;
	}

	auto MovementComponent::GetSpeed() const -> float
	{
		return _movement.speed;
	}

	void MovementComponent::SetMovement(const Movement& movement)
	{
		_movement = movement;

		if (_movement.IsMoving())
		{
			_startPosition = movement.position;
			_lastMovementTimePoint = clock_t::now();
		}
	}

	void MovementComponent::SetPosition(const Vector3D& position)
	{
		_movement.position = position;
	}

	void MovementComponent::SetDestination(const Vector3D& position)
	{
		_movement.destPosition = position;
	}

	void MovementComponent::SetDirection(float value)
	{
		_movement.direction = value;
	}

	void MovementComponent::SetSpeed(float value)
	{
		_movement.speed = value;
	}

	void MovementComponent::SetMoving(bool value)
	{
		_movement.SetMoving(value);
	}

	void MovementComponent::OnTick(time_point_t now)
	{
		if (!_movement.IsMoving())
		{
			return;
		}

		if (_movement.position.IsNearlyEqual(_movement.destPosition))
		{
			return;
		}

		if (_time == 1.f)
		{
			return;
		}

		using std::chrono::duration_cast;
		using std::chrono::duration;

		float deltaMS = duration_cast<duration<float, std::milli>>(now - _lastMovementTimePoint).count();
		float time = deltaMS / _dist.GetSize() * _movement.speed * 0.1f;

		_time = std::min(1.f, _time + time);

		_movement.position = Lerp(_startPosition, _movement.destPosition, _time);

		if (_time == 1.f)
		{
			_movement.SetMoving(false);
		}

		_lastMovementTimePoint = now;
	}
}

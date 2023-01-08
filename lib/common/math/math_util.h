#pragma once
#include "lib/common/math/vector.h"

namespace cebreiro
{
	auto GetAngleRadian(float x0, float y0, float x1, float y1) -> float;

	auto Lerp(const Vector3D& v0, const Vector3D& v1, float t)->Vector3D;

	auto ToRadian(float degree) -> float;
	auto ToDegree(float radian) -> float;
}

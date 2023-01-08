#include "math_util.h"

#include <cmath>
#include <DirectXMath.h>

namespace cebreiro
{
	auto GetAngleRadian(float x0, float y0, float x1, float y1) -> float
	{
		float x = x1 - x0;
		float y = y1 - y0;
		return std::atan2f(y, x);
	}

	auto Lerp(const Vector3D& v0, const Vector3D& v1, float t) -> Vector3D
	{
		using namespace DirectX;

		XMVECTOR p1 = XMLoadFloat3(&v0.GetMatrix());
		XMVECTOR p2 = XMLoadFloat3(&v1.GetMatrix());

		XMFLOAT3 ret;
		XMStoreFloat3(&ret, XMVectorLerp(p1, p2, t));

		return Vector3D(ret);
	}

	auto ToRadian(float degree) -> float
	{
		return DirectX::XMConvertToRadians(degree);
	}

	auto ToDegree(float radian) -> float
	{
		return DirectX::XMConvertToDegrees(radian);
	}
}

#include "vector.h"

#include <cmath>
#include <limits>

namespace cebreiro
{
	Vector3D::Vector3D()
		: Vector3D(0.f, 0.f, 0.f)
	{
	}

	Vector3D::Vector3D(float x, float y, float z)
		: _float3(x, y, z)
	{
	}

	Vector3D::Vector3D(const Matrix1X2& matrix1X2)
		: Vector3D(matrix1X2.x, matrix1X2.y, 0.f)
	{

	}

	Vector3D::Vector3D(const Matrix1X3& matrix1X3)
		: _float3(matrix1X3)
	{
	}

	bool Vector3D::IsNearlyZero() const noexcept
	{
		constexpr float epsilon = std::numeric_limits<float>::epsilon();

		return std::abs(_float3.x) <= epsilon
			&& std::abs(_float3.y) <= epsilon
			&& std::abs(_float3.z) <= epsilon;
	}

	bool Vector3D::IsNearlyEqual(const Vector3D& other) const noexcept
	{
		return ((*this) - other).IsNearlyZero();
	}

	float Vector3D::GetSize() const noexcept
	{
		using namespace DirectX;

		return XMVector3Length(XMLoadFloat3(&_float3)).m128_f32[0];
	}

	float Vector3D::GetSizeSquared() const noexcept
	{
		using namespace DirectX;

		return XMVector3LengthSq(XMLoadFloat3(&_float3)).m128_f32[0];
	}

	float Vector3D::GetX() const noexcept
	{
		return _float3.x;
	}

	float Vector3D::GetY() const noexcept
	{
		return _float3.y;
	}

	float Vector3D::GetZ() const noexcept
	{
		return _float3.z;
	}

	void Vector3D::SetX(float x) noexcept
	{
		_float3.x = x;
	}

	void Vector3D::SetY(float y) noexcept
	{
		_float3.y = y;
	}

	void Vector3D::SetZ(float z) noexcept
	{
		_float3.z = z;
	}

	void Vector3D::SetXY(float x, float y) noexcept
	{
		_float3.x = x;
		_float3.y = y;
	}

	void Vector3D::SetXYZ(float x, float y, float z) noexcept
	{
		_float3.x = x;
		_float3.y = y;
		_float3.z = z;
	}

	Vector3D Vector3D::operator+(const Vector3D& other) const noexcept
	{
		return Vector3D(
			_float3.x + other._float3.x,
			_float3.y + other._float3.y,
			_float3.z + other._float3.z
		);
	}

	Vector3D Vector3D::operator-(const Vector3D& other) const noexcept
	{
		return Vector3D(
			_float3.x - other._float3.x,
			_float3.y - other._float3.y,
			_float3.z - other._float3.z
		);
	}

	bool Vector3D::operator==(const Vector3D& other) const noexcept
	{
		return _float3.x == other._float3.x
			&& _float3.y == other._float3.y
			&& _float3.z == other._float3.z;
	}

	bool Vector3D::operator!=(const Vector3D& other) const noexcept
	{
		return !operator==(other);
	}

	float Vector3D::Dot(const Vector3D& other) const noexcept
	{
		using namespace DirectX;

		XMVECTOR v1 = XMLoadFloat3(&_float3);
		XMVECTOR v2 = XMLoadFloat3(&other._float3);

		return XMVector3Dot(v1, v2).m128_f32[0];
	}

	Vector3D Vector3D::Cross(const Vector3D& other) const noexcept
	{
		using namespace DirectX;

		XMVECTOR v1 = XMLoadFloat3(&_float3);
		XMVECTOR v2 = XMLoadFloat3(&other._float3);

		XMFLOAT3 ret;
		XMStoreFloat3(&ret, XMVector3Cross(v1, v2));

		return Vector3D(ret);
	}

	Vector3D Vector3D::Normalize() const noexcept
	{
		using namespace DirectX;

		XMVECTOR v1 = XMLoadFloat3(&_float3);

		XMFLOAT3 ret;
		XMStoreFloat3(&ret, XMVector3Normalize(v1));

		return Vector3D(ret);
	}

	auto Vector3D::GetMatrix() const -> const Matrix1X3&
	{
		return _float3;
	}
}

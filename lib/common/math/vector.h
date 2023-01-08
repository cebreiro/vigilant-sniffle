#pragma once
#include "matrix.h"

namespace cebreiro
{
	class Vector3D
	{
		friend class MathUtil;
	public:
		Vector3D();
		Vector3D(float x, float y, float z);
		explicit Vector3D(const Matrix1X2& matrix1X2);
		explicit Vector3D(const Matrix1X3& matrix1X3);

		bool IsNearlyZero() const noexcept;
		bool IsNearlyEqual(const Vector3D& other) const noexcept;

		float GetSize() const noexcept;
		float GetSizeSquared() const noexcept;

		float GetX() const noexcept;
		float GetY() const noexcept;
		float GetZ() const noexcept;

		void SetX(float x) noexcept;
		void SetY(float y) noexcept;
		void SetZ(float z) noexcept;
		void SetXY(float x, float y) noexcept;
		void SetXYZ(float x, float y, float z) noexcept;

		Vector3D operator+(const Vector3D& other) const noexcept;
		Vector3D operator-(const Vector3D& other) const noexcept;
		bool operator==(const Vector3D& other) const noexcept;
		bool operator!=(const Vector3D& other) const noexcept;

		float Dot(const Vector3D& other) const noexcept;
		Vector3D Cross(const Vector3D& other) const noexcept;
		Vector3D Normalize() const noexcept;

		auto GetMatrix() const -> const Matrix1X3&;

	private:
		Matrix1X3 _float3;
	};
}
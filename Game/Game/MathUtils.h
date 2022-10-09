// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
// (c) 2022 Media Design School
//
// File Name: MathUtils.h
// Description: Math utils initialization file
// Authors: Michael Wai Kit Tran

#pragma once
#include <cmath>
#define PI 3.141592653589793238463f

namespace sf
{
	template <typename T>
	class Vector2;
	typedef Vector2<float> Vector2f;

	template <typename T>
	class Vector3;
	typedef Vector3<float> Vector3f;

	const float Magnitude(const Vector2f _vector);

	const float Magnitude(const Vector3f _vector);

	const Vector2f Normalise(const Vector2f _vector);

	const Vector3f Normalise(const Vector3f _vector);

	const float Distance(const Vector2f _A, const Vector2f _B);

	const float Distance(const Vector3f _A, const Vector3f _B);

	const Vector2f Truncate(const Vector2f _vector, float _maxMagnitude);

	const Vector3f Truncate(const Vector3f _vector, float _maxMagnitude);

	const float Dot(const Vector2f _A, const Vector2f _B);

	const float Dot(const Vector3f _A, const Vector3f _B);

	const Vector3f Cross(const Vector3f _A, const Vector3f _B);

	const float Lerp(const float _A, const float _B, const float _T);

	const Vector2f Lerp(const Vector2f _A, const Vector2f _B, const float _T);
}
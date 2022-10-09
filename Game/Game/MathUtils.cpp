// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
// (c) 2022 Media Design School
//
// File Name: MathUtils.cpp
// Description: Math utils declaration file
// Authors: Michael Wai Kit Tran

#include "MathUtils.h"
#include "SFML/System/Vector2.hpp"
#include "SFML/System/Vector3.hpp"

using namespace std;

const float sf::Magnitude(const sf::Vector2f _vector)
{
	return sqrtf((_vector.x * _vector.x) + (_vector.y * _vector.y));
}

const float sf::Magnitude(const sf::Vector3f _vector)
{
	return sqrtf((_vector.x * _vector.x) + (_vector.y * _vector.y) + (_vector.z * _vector.z));
}

const sf::Vector2f sf::Normalise(const sf::Vector2f _vector)
{
	float&& magnitude = Magnitude(_vector);

	if (magnitude != 0) return _vector / magnitude;
	else return sf::Vector2f();
}

const sf::Vector3f sf::Normalise(const sf::Vector3f _vector)
{
	float&& magnitude = Magnitude(_vector);

	if (magnitude != 0) return _vector / magnitude;
	else return sf::Vector3f();
}

const float sf::Distance(const sf::Vector2f _A, const sf::Vector2f _B)
{
	return Magnitude(_B - _A);
}

const float sf::Distance(const sf::Vector3f _A, const sf::Vector3f _B)
{
	return Magnitude(_B - _A);
}

const sf::Vector2f sf::Truncate(const sf::Vector2f _vector, float _maxMagnitude)
{
	if (Magnitude(_vector) > _maxMagnitude) return Normalise(_vector) * _maxMagnitude;
	else return _vector;
}

const sf::Vector3f sf::Truncate(const sf::Vector3f _vector, float _maxMagnitude)
{
	if (Magnitude(_vector) > _maxMagnitude) return Normalise(_vector) * _maxMagnitude;
	else return _vector;
}

const float sf::Dot(const sf::Vector2f _A, const sf::Vector2f _B)
{
	return (_A.x * _A.x) + (_A.y * _A.y);
}

const float sf::Dot(const sf::Vector3f _A, const sf::Vector3f _B)
{
	return (_A.x * _A.x) + (_A.y * _A.y) + (_A.z * _A.z);
}

const sf::Vector3f sf::Cross(const sf::Vector3f _A, const sf::Vector3f _B)
{
	return sf::Vector3f
	(
		(_A.y * _B.z) - (_A.z * _B.y),
		(_A.z * _B.x) - (_A.x * _B.z),
		(_A.x * _B.y) - (_A.y * _B.x)
	);
}

const float sf::Lerp(const float _A, const float _B, const float _T)
{
	return _A + ((_B - _A) * _T);
}

const sf::Vector2f sf::Lerp(const Vector2f _A, const Vector2f _B, const float _T)
{
	return _A + ((_B - _A) * _T);
}

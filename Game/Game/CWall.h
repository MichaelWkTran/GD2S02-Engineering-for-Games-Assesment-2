#pragma once
#include "CMapPlaceBase.h"

//[Delete later on] Tag of the wall has been changed from "UnbreakableWall" to "Wall"
class CWall : public CMapPlaceBase
{
public:
	bool isBreakable;
	float health;

	CWall(sf::Vector2f _pos, float _rotation, bool _isBreakable = false);
	void TakeDamage(float _damage);
};
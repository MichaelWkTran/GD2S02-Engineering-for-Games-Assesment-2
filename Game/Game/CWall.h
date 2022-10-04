#pragma once
#include "CMapPlaceBase.h"
#include "CPhysicsBody.h"

//[Delete later on] Tag of the wall has been changed from "UnbreakableWall" to "Wall"
class CWall : public CPhysicsBody, public CMapPlaceBase
{
public:
	bool isBreakable;
	float health;

	CWall(sf::Vector2f _pos, float _rotation, bool _isBreakable = false);

	virtual void BeginContact(CPhysicsBody* _other);
};
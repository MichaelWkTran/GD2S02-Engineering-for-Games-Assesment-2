#pragma once
#include "CGameObject.h"
#include "CPhysicsBody.h"

class CSpikeTrap : public CGameObject, public CPhysicsBody
{
public:
	static float damage;

	CSpikeTrap(sf::Vector2f _pos);
};


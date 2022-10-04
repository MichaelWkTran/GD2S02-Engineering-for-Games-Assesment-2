#pragma once
#include "CGameObject.h"
#include "CPhysicsBody.h"
#include <set>

class CPlayer;

class CSpikeTrap : public CPhysicsBody, public CGameObject
{
public:
	std::set<CPlayer*> playersCollidedWith;
	static float damage;

	CSpikeTrap(sf::Vector2f _pos);
	virtual void Update() override;

	virtual void BeginContact(CPhysicsBody* _other) override;
	virtual void EndContact(CPhysicsBody* _other) override;
};


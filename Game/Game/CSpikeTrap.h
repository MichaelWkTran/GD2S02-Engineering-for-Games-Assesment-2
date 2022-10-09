// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
// (c) 2022 Media Design School
//
// File Name: CSpikeTrap.h
// Description: CSpikeTrap initialization file
// Authors: Michael Wai Kit Tran

#pragma once
#include "CMapPlaceBase.h"
#include "CPhysicsBody.h"
#include <set>

class CPlayer;

class CSpikeTrap : public CPhysicsBody, public CMapPlaceBase
{
public:
	std::set<CPlayer*> playersCollidedWith;
	static float damage;

	CSpikeTrap(sf::Vector2f _pos);
	virtual void Update() override;

	virtual void BeginContact(CPhysicsBody* _other) override;
	virtual void EndContact(CPhysicsBody* _other) override;
};


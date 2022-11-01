// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
// (c) 2022 Media Design School
//
// File Name: CPhysicsBody.h
// Description: CPhysicsBody initialization file
// Authors: Michael Wai Kit Tran

#pragma once
#include "CGameObject.h"
#include "Box2D/box2d.h"

class CPhysicsBody
{
protected:
	b2Body* body = nullptr;
	unsigned int fixtureCount;

public:
	CPhysicsBody();
	virtual ~CPhysicsBody();
	virtual void FixedUpdate() {};

	// setup methods
	void SetupBody(const b2BodyDef& _BodyDef, const b2FixtureDef* _pFixtureDef, unsigned int _size);

	// collision Methods
	virtual void BeginContact(CPhysicsBody* _other) {};
	virtual void EndContact(CPhysicsBody* _other) {};
	virtual void PreSolve(CPhysicsBody* _other, const b2Manifold* _oldManifold) {};
	virtual void PostSolve(CPhysicsBody* _other, const b2ContactImpulse* _impulse) {};

	// get set methods
	b2Body& GetBody() const { return *body; }
	operator b2Body* () const { return body; }
	const unsigned int GetFixtureCount() const { return fixtureCount; }
};
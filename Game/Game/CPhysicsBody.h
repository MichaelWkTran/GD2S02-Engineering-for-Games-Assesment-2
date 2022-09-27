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
	~CPhysicsBody();

	// setup methods
	void SetupBody(const b2BodyDef& _bodyDef, const b2FixtureDef* _fixtureDef, unsigned int _size);
	
	// collision nethods
	virtual void BeginContact(CPhysicsBody* _pOther) {};
	virtual void EndContact(CPhysicsBody* _pOther) {};
	virtual void PreSolve(CPhysicsBody* _pOther, const b2Manifold* _pOldManifold) {};
	virtual void PostSolve(CPhysicsBody* _pOther, const b2ContactImpulse* _pImpulse) {};

	// get set methods
	b2Body& GetBody() const { return *body; }
	operator b2Body* () const { return body; }
	const unsigned int GetFixtureCount() const { return fixtureCount; }
};
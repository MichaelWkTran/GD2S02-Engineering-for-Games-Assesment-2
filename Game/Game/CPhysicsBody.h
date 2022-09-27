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

	void SetupBody(const b2BodyDef _bodyDef, const b2FixtureDef* _fixtureDef, unsigned int _size);

	b2Body& GetBody() const { return *body; }
};
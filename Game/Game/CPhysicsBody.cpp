#include "CPhysicsBody.h"
#include "CManager.h"

CPhysicsBody::CPhysicsBody()
{
	body = nullptr;
	fixtureCount = 0U;
}

CPhysicsBody::~CPhysicsBody()
{
	GetManager().GetPhysicsWorld().DestroyBody(body);
}

void CPhysicsBody::SetupBody(const b2BodyDef _bodyDef, const b2FixtureDef* _fixtureDef, unsigned int _size)
{
	// create b2Body from physics world
	body = GetManager().GetPhysicsWorld().CreateBody(&_bodyDef);

	// create fixtures to be used by the body
	for (unsigned int i = 0; i < _size; i++) body->CreateFixture(_fixtureDef + i);
	fixtureCount = _size;
}
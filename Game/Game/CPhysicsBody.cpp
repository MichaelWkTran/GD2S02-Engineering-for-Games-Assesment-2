#include "CPhysicsBody.h"
#include "Box2D/box2d.h"
#include "CManager.h"

CPhysicsBody::CPhysicsBody()
{
	body = nullptr;
	fixtureCount = 0U;
}

CPhysicsBody::~CPhysicsBody()
{
	if (body != nullptr)
	{
		GetManager().GetPhysicsWorld().DestroyBody(body);
	}
}

void CPhysicsBody::SetupBody(const b2BodyDef& _bodyDef, const b2FixtureDef* _fixtureDef, unsigned int _size)
{
	body = GetManager().GetPhysicsWorld().CreateBody(&_bodyDef);
	body->GetUserData().pointer = reinterpret_cast<uintptr_t>(this); //(uintptr_t)static_cast<void*>(this);

	for (unsigned int i = 0; i < _size; i++) body->CreateFixture(_fixtureDef + i);
	fixtureCount = _size;
}
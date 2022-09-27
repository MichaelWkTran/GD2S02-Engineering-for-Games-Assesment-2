#include "CPhysicsBody.h"
#include "CManager.h"

CPhysicsBody::CPhysicsBody()
{
	body = nullptr;
	shape = nullptr;
}

CPhysicsBody::~CPhysicsBody()
{
	GetManager().GetPhysicsWorld().DestroyBody(body);
}

void CPhysicsBody::SetupBody()
{
	body = GetManager().GetPhysicsWorld().CreateBody(&bodyDef);
	body->CreateFixture(&fixtureDef);
}
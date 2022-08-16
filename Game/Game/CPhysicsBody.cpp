#include "CPhysicsBody.h"
#include "CManager.h"

CPhysicsBody::CPhysicsBody()
{
	m_pBody = nullptr;
	m_pShape = nullptr;
}

CPhysicsBody::~CPhysicsBody()
{
	GetManager().GetPhysicsWorld().DestroyBody(m_pBody);
}

void CPhysicsBody::SetupBody()
{
	m_pBody = GetManager().GetPhysicsWorld().CreateBody(&m_BodyDef);
	m_pBody->CreateFixture(&m_FixtureDef);
}
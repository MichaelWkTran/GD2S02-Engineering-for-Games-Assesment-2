#pragma once
#include "CGameObject.h"
#include "Box2D/box2d.h"

class CPhysicsBody
{
protected:
	b2Body* m_pBody;
	b2Shape* m_pShape;

public:
	b2BodyDef m_BodyDef;
	b2FixtureDef m_FixtureDef;

	CPhysicsBody();
	~CPhysicsBody();

	void SetupBody();
	template <class T>
	void SetupShape();

	b2Body& GetBody() const { return *m_pBody; }
	b2Shape& GetShape() const { return *m_pShape; }
};

//The template class, T, must inherit from b2Shape
template<class T>
inline void CPhysicsBody::SetupShape()
{
	m_pShape = new T;
	m_FixtureDef.shape = m_pShape;
};
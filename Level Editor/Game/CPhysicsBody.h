#pragma once
#include "CGameObject.h"
#include "Box2D/box2d.h"

class CPhysicsBody
{
protected:
	b2Body* body = nullptr;
	b2Shape* shape = nullptr;

public:
	b2BodyDef bodyDef;
	b2FixtureDef fixtureDef;

	CPhysicsBody();
	~CPhysicsBody();

	void SetupBody();
	template <class T>
	void SetupShape();

	b2Body& GetBody() const { return *body; }
	b2Shape& GetShape() const { return *shape; }
};

// the template class, T, must inherit from b2Shape
template<class T>
inline void CPhysicsBody::SetupShape()
{
	shape = new T;
	fixtureDef.shape = shape;
};
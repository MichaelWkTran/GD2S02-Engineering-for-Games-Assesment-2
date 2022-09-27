#include "CBullet.h"
#include "CPhysicsBody.h"
#include "CManager.h"
#include <iostream>

CBullet::CBullet(float _damage, float _moveSpeed, sf::Vector2f _spawnPosition, b2Vec2 _velocity)
{
	damage = _damage;
	moveSpeed = _moveSpeed;
	velocity = _velocity;

	velocity *= moveSpeed;

	tags.emplace("Bullet");

	// setup CGameObject
	float radius = 4.0f;

	// set the origin of the SFML transform
	transform.setOrigin(radius, radius);

	// setup sf::Drawable
	drawable = new sf::CircleShape(radius);
	((sf::CircleShape*)drawable)->setFillColor(sf::Color().Blue);
	transform.setPosition(_spawnPosition);

	// setup b2BodyDef
	physicsBody = new CPhysicsBody;
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.bullet = true;
	bodyDef.position = GetManager().pixelToWorldScale * b2Vec2(transform.getPosition().x, transform.getPosition().y);

	// setup b2Shape
	b2CircleShape shape;
	shape.m_radius = radius * GetManager().pixelToWorldScale;

	// setup b2FixtureDef
	b2FixtureDef fixtureDef;
	fixtureDef.density = 1.0f;
	fixtureDef.shape = &shape;

	// setup b2Body
	physicsBody->SetupBody(bodyDef, &fixtureDef, 1);
	physicsBody->GetBody().GetUserData().pointer = reinterpret_cast<uintptr_t>(this);
}

CBullet::~CBullet()
{
	
}

void CBullet::Update()
{
	lifeTime -= GetManager().deltatime;
	if (lifeTime < 0)
	{
		DeleteObject();
	}
	physicsBody->GetBody().SetLinearVelocity(velocity);
}

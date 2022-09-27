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
	physicsBody->bodyDef.type = b2_dynamicBody;
	physicsBody->bodyDef.bullet = true;

	// setup b2Shape
	physicsBody->SetupShape<b2CircleShape>();
	physicsBody->GetShape().m_radius = radius * GetManager().pixelToWorldScale;

	// setup b2FixtureDef
	physicsBody->fixtureDef.density = 1.0f;
	physicsBody->bodyDef.position = b2Vec2(transform.getPosition().x * GetManager().pixelToWorldScale, transform.getPosition().y * GetManager().pixelToWorldScale);

	// setup b2Body
	physicsBody->SetupBody();
	physicsBody->GetBody().GetUserData().pointer = (uintptr_t)static_cast<void*>(this);
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

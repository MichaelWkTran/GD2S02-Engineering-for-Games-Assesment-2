#include "CBullet.h"
#include "CPhysicsBody.h"
#include "CManager.h"
#include <iostream>

CBullet::CBullet(float _damage, float _moveSpeed, sf::Vector2f _spawnPosition)
{
	damage = _damage;
	moveSpeed = _moveSpeed;

	// setup CGameObject
	float radius = 4.0f;

	// set the origin of the SFML transform
	transform.setOrigin(sf::Vector2f(radius, radius));

	// setup sf::Drawable
	drawable = new sf::CircleShape(radius);
	((sf::CircleShape*)drawable)->setFillColor(sf::Color().Blue);
	transform.setPosition(_spawnPosition);

	// setup b2BodyDef
	physicsBody = new CPhysicsBody;
	physicsBody->bodyDef.type = b2_dynamicBody;

	// setup b2Shape
	physicsBody->SetupShape<b2CircleShape>();
	physicsBody->GetShape().m_radius = radius * GetManager().pixelToWorldScale;

	// setup b2FixtureDef
	physicsBody->fixtureDef.density = 1.0f;

	// setup b2Body
	physicsBody->SetupBody();
}

CBullet::~CBullet()
{
}

void CBullet::Update()
{
	b2Vec2 movement = b2Vec2
	(
		1, 0
	);
	movement.Normalize();
	movement *= moveSpeed;
	
	physicsBody->GetBody().SetLinearVelocity(movement);
}

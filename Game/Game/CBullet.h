#pragma once
#include "CGameObject.h"
#include "CPhysicsBody.h"
#include "Box2D/b2_body.h"

class CBullet : public CPhysicsBody, public CGameObject
{
public:
	float damage;
	float moveSpeed;
	float projectileMomentum;
	float projectileRange;
	b2Vec2 velocity;

	CBullet(float _damage, float _moveSpeed, float _momentum, float _projectileRange, sf::Vector2f _spawnPosition, b2Vec2 _velocity);

	virtual void Update() override;

	virtual void BeginContact(CPhysicsBody* _other) override;
};


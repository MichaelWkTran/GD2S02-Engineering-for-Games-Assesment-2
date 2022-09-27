#pragma once
#include "CGameObject.h"
#include "Box2D/b2_body.h"

class CBullet : public CGameObject
{
public:
	float damage;
	float moveSpeed;
	float lifeTime = 5.0f;
	b2Vec2 velocity;

	CBullet(float _damage, float _moveSpeed, sf::Vector2f _spawnPosition, b2Vec2 _velocity);
	~CBullet();

	virtual void Update() override;
};


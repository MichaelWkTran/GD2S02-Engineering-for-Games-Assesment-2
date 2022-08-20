#pragma once
#include "CGameObject.h"
class CBullet : public CGameObject
{
public:
	float damage;
	float moveSpeed;

	CBullet(float _damage, float _moveSpeed, sf::Vector2f _spawnPosition);
	~CBullet();

	virtual void Update() override;
};


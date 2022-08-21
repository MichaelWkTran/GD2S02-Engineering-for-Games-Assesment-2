#pragma once
#include "CGameObject.h"
#include "Box2D/box2d.h"

class CGun;

class CPlayer : public CGameObject
{
public:
	float maxHealth;
	float health;
	float moveSpeed;
	float coolDown;
	b2Vec2 facingDirection;
	CGun* heldGun = nullptr;

	CPlayer();
	~CPlayer();

	virtual void Update() override;
	void AddGunToRender();
};


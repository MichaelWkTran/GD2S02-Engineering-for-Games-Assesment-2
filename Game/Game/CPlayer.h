#pragma once
#include "CGameObject.h"
#include "Box2D/box2d.h"

class CBullet;

class CPlayer : public CGameObject
{
public:
	float maxHealth;
	float health;
	float moveSpeed;
	float coolDown;

	CPlayer();
	~CPlayer();

	virtual void Update() override;
};


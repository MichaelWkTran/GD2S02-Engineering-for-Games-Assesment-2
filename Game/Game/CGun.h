#pragma once
#include "CGameObject.h"
#include <Box2D/b2_body.h>
class CPlayer;

class CGun : public CGameObject
{
private:
	float counterFireRate = 0.0f;
public:
	float damage = 1;
	float bulletSpeed = 3;
	float bulletCount = 1;
	float fireRate = 0.5f;
	b2Vec2* playerFacingDirection = nullptr;
	CPlayer* ownerPlayer = nullptr;

	CGun(b2Vec2* _playerFaceDirection, CPlayer* _player);
	~CGun();

	virtual void Update() override;

	void Shoot();
};


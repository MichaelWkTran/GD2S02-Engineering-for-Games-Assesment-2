// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
// (c) 2022 Media Design School
//
// File Name : CWeapons.h
// Description: header file for CWeapons class
// Authors: Lucas Manssen

#pragma once
#include "CBullet.h"
#include "CPlayer.h"
#include "CGameObject.h"
#include <Box2D/b2_body.h>

// placeholder values
/*weapons:
* Pistol: avg fire rate:0.5, avg speed, 1 projectile, small momentum, no knockback
* Rifle: fast fire rate, avg-fast speed, 1 projectile, medium momentum, medium knockback
* Sniper: very slow fire rate, very fast speed, 1 projectile, large momentum, large knockback
* Shotgun: slow fire rate, average speed, 3 projectiles, small life span, large momentum, medium knockback
*/

class CWeapons : public CGameObject
{
private:
	float fireRate = 0;
	float projectileSpeed = 0;
	int numberOfProjectiles = 0;
	float projectileMomentum = 0;
	float projectileRange = 0;
	int damage = 0;
	float weaponLength = 5; // will need to eventually add unique weapon lengths based on sprite
	int currentWeapon = -1;
	// eventually need to add rectangle shape and texture for each weapon

public:
	CBullet* projectile = nullptr;
	CPlayer* playerObject = nullptr;
	b2Vec2* playerFacingVector = nullptr;
	sf::Transformable transform;
	//sf::Drawable* drawable;
	sf::RectangleShape* gunBox;
	sf::Texture* gunTex;


	float fireRateCounter = 0;
	float recoilForce = 0;

	CWeapons(b2Vec2* _playerFacingVec, CPlayer* _playerObject, int _weaponInt);
	~CWeapons();

	int GetCurrentWeapon();

	void Update();
	virtual void Draw() override;
	void Shoot();
};


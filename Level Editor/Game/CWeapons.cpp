// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
// (c) 2022 Media Design School
//
// File Name : CWeapons.cpp
// Description: methods of CWeapons class
// Authors: Lucas Manssen

#include "CWeapons.h"
#include "CManager.h"
#include "CBullet.h"
#include "CPlayer.h"
#include <iostream>

CWeapons::CWeapons(b2Vec2* _playerFacingVec, CPlayer* _playerObject, int _weaponInt)
{
	// set up player host object
	playerFacingVector = _playerFacingVec;
	playerObject = _playerObject;

	// set up weapon parameters
	// If weapon is Pistol
	if (_weaponInt == 0)
	{
		fireRate = 2;
		projectileSpeed = 2;
		recoilForce = 0;
		numberOfProjectiles = 1;
		projectileMomentum = 1;
		innaccuracyModifier = 0;
		projectileRange = 30;
		damage = 1;
	}

	// If weapon is Rifle
	if (_weaponInt == 1)
	{
		fireRate = 1.5;
		projectileSpeed = 3;
		recoilForce = 1;
		numberOfProjectiles = 1;
		projectileMomentum = 2;
		innaccuracyModifier = 5;
		projectileRange = 40;
		damage = 2;
	}

	// If weapon is Sniper
	if (_weaponInt == 2)
	{
		fireRate = 0.4;
		projectileSpeed = 6;
		recoilForce = 4;
		numberOfProjectiles = 1;
		projectileMomentum = 6;
		innaccuracyModifier = 0;
		projectileRange = 100;
		damage = 5;
	}

	// If weapon is Shotgun
	if (_weaponInt == 3)
	{
		fireRate = 0.8;
		projectileSpeed = 3;
		recoilForce = 3;
		numberOfProjectiles = 3;
		projectileMomentum = 6;
		innaccuracyModifier = 15;
		projectileRange = 15;
		damage = 3;
	}

	currentWeapon = _weaponInt;
	// set up game object
	float radius = 40.f;
	transform.setOrigin(sf::Vector2f(radius / 4, radius));

	// set up drawable
	// will need to add sprite
	drawable = new sf::RectangleShape(sf::Vector2f(radius / 2, radius));
	((sf::CircleShape*)drawable)->setFillColor(sf::Color::Black);
	transform.setPosition(playerObject->transform.getPosition());

	// rotate drawable based on player facing vector
	switch ((int)playerFacingVector->x)
	{
	case 0:
		switch ((int)playerFacingVector->y)
		{
		case -1:
			transform.setRotation(0);
			break;
		case 1:
			transform.setRotation(180);
			break;
		}
		break;
	case -1:
		switch ((int)playerFacingVector->y)
		{
		case 0:
			transform.setRotation(-90);
			break;
		case -1:
			transform.setRotation(-45);
			break;
		case 1:
			transform.setRotation(-135);
			break;
		}
		break;
	case 1:
		switch ((int)playerFacingVector->y)
		{
		case 0:
			transform.setRotation(90);
			break;
		case -1:
			transform.setRotation(45);
			break;
		case 1:
			transform.setRotation(135);
			break;
		}
		break;
	}
}

CWeapons::~CWeapons()
{
}

// returns integer of current weapon
int CWeapons::GetCurrentWeapon()
{
	return currentWeapon;
}

//update rotation, position and shot cooldown timer
void CWeapons::Update()
{
	// update counter until able to shoot again
	if (fireRateCounter < fireRate)
	{
		fireRateCounter += GetManager().deltatime;
	}

	// update the current rotation
	if ((int)playerFacingVector->x > 0)
	{
		if ((int)playerFacingVector->y > 0)
		{
			transform.setRotation(135);
		}
		else if ((int)playerFacingVector->y < 0)
		{
			transform.setRotation(45);
		}
		else
		{
			transform.setRotation(90);
		}
	}
	else if ((int)playerFacingVector->x == 0)
	{
		if ((int)playerFacingVector->y > 0)
		{
			transform.setRotation(180);
		}
		else if ((int)playerFacingVector->y < 0)
		{
			transform.setRotation(0);
		}
	}
	else
	{

		if ((int)playerFacingVector->y > 0)
		{
			transform.setRotation(-135);
		}
		else if ((int)playerFacingVector->y < 0)
		{
			transform.setRotation(-45);
		}
		else
		{
			transform.setRotation(-90);
		}
	}

	// update position
	sf::Drawable* playerDrawable = playerObject->GetDrawable();
	transform.setPosition(dynamic_cast<sf::Transformable*>(playerDrawable)->getPosition());
}

// fire the weapon object, impart recoil to player object
void CWeapons::Shoot()
{
	if (fireRateCounter >= fireRate)
	{
		// spawn bullet at end of weapon
		sf::Vector2f projectileSpawnPos = sf::Vector2f(dynamic_cast<sf::Transformable*>(drawable)->getPosition().x + playerFacingVector->x * weaponLength, dynamic_cast<sf::Transformable*>(drawable)->getPosition().y + playerFacingVector->y * weaponLength);
		//spawn bullets with for loop
		for (int i = 0; i < numberOfProjectiles; i++)
		{
			// spawn bullet
			// will need to be changed to allow for innaccuracy (rifle, shotgun spread)
			// will need to be changed to allow for momentum
			// will need to be changed to allow for projectile range
			new CBullet(damage, projectileSpeed, projectileSpawnPos, *playerFacingVector);
		}
		// will need to add player recoil here
	}
}

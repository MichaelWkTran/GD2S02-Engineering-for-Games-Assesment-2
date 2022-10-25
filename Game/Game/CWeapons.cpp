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
#include "CSound.h"
#include "SFML/Graphics.hpp"
#include <iostream>

// contstructor
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
		projectileRange = 5;
		damage = 1;
		gunTex = new sf::Texture();
		gunTex->loadFromFile("Assets/Sprites/weaponSprites/topDownPistol2.png");
	}

	// If weapon is Rifle
	if (_weaponInt == 1)
	{
		fireRate = 1;
		projectileSpeed = 3;
		recoilForce = 1;
		numberOfProjectiles = 1;
		projectileMomentum = 2;
		projectileRange = 7;
		damage = 2;
		gunTex = new sf::Texture();
		gunTex->loadFromFile("Assets/Sprites/weaponSprites/topDownRifle2.png");
	}

	// If weapon is Sniper
	if (_weaponInt == 2)
	{
		fireRate = 5;
		projectileSpeed = 6;
		recoilForce = 4;
		numberOfProjectiles = 1;
		projectileMomentum = 6;
		projectileRange = 100;
		damage = 5;
		gunTex = new sf::Texture();
		gunTex->loadFromFile("Assets/Sprites/weaponSprites/topDownSniper2.png");
	}

	// If weapon is Shotgun
	if (_weaponInt == 3)
	{
		fireRate = 4;
		projectileSpeed = 2;
		recoilForce = 3;
		numberOfProjectiles = 3;
		projectileMomentum = 6;
		projectileRange = 3;
		damage = 3;
		gunTex = new sf::Texture();
		gunTex->loadFromFile("Assets/Sprites/weaponSprites/topDownShotgun2.png");
	}

	currentWeapon = _weaponInt;
	// set up game object
	float radius = 40.f;

	transform.setOrigin(sf::Vector2f(12.f, 75.f));

	// set up drawable
	// will need to add sprite
	gunBox = new sf::RectangleShape(sf::Vector2f(24.f, 60.f));
	((sf::CircleShape*)gunBox)->setFillColor(sf::Color().White);
	transform.setPosition(playerObject->transform.getPosition());
	gunBox->setTexture(gunTex);

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
	fireRateCounter = 100;
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
		fireRateCounter += GetManager().deltaTime;
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
	if (playerObject != nullptr)
	{
		sf::Drawable* playerDrawable = playerObject->GetDrawable();
		transform.setPosition(dynamic_cast<sf::Transformable*>(playerDrawable)->getPosition());
	}
	else
	{
		DeleteObject();
	}
}

// repostition and draw weapon box to frame
void CWeapons::Draw()
{
	sf::Transformable* drawableTransform = dynamic_cast<sf::Transformable*>(gunBox);
	if (drawableTransform == nullptr)
	{
		std::cout << "ERROR: m_Drawable in CGameObject must inherit from sf::Transformable\n";
		return;
	}

	drawableTransform->setPosition(transform.getPosition());
	drawableTransform->setScale(transform.getScale());
	drawableTransform->setRotation(transform.getRotation());
	drawableTransform->setOrigin(transform.getOrigin());

	GetManager().GetWindow().draw(*gunBox);
}

// fire the weapon object, impart recoil to player object
void CWeapons::Shoot()
{
	if (fireRateCounter >= fireRate)
	{
		// spawn bullet at end of weapon
		sf::Vector2f projectileSpawnPos = sf::Vector2f(dynamic_cast<sf::Transformable*>(gunBox)->getPosition().x + playerFacingVector->x * weaponLength, dynamic_cast<sf::Transformable*>(gunBox)->getPosition().y + playerFacingVector->y * weaponLength);
		//spawn bullets with for loop
		if (numberOfProjectiles == 1)
		{
			// spawn bullet
			new CBullet((float)damage, projectileSpeed, projectileMomentum, projectileRange, projectileSpawnPos, *playerFacingVector);
			new CSound("gun7.wav");
		}
		else if (numberOfProjectiles == 3)
		{
			// spawn bullet
			new CBullet((float)damage, projectileSpeed, projectileMomentum, projectileRange, projectileSpawnPos, *playerFacingVector);
			new CBullet((float)damage, projectileSpeed, projectileMomentum, projectileRange, projectileSpawnPos, b2Vec2(playerFacingVector->x - 1.0f, playerFacingVector->y + 0.5f));
			new CBullet((float)damage, projectileSpeed, projectileMomentum, projectileRange, projectileSpawnPos, b2Vec2(playerFacingVector->x - 0.5f, playerFacingVector->y + 1.0f));
			new CSound("gun1.wav");
		}
		fireRateCounter = 0;
		
		// calculate and apply recoil vector force
		b2Vec2 recoil;
		if ((int)playerFacingVector->x > 0)
		{
			if ((int)playerFacingVector->y > 0)
			{
				recoil = b2Vec2(recoilForce * -10.f, recoilForce * -10.f);
				playerObject->ApplyRecoil(recoil);
			}
			else if ((int)playerFacingVector->y < 0)
			{
				recoil = b2Vec2(recoilForce * -10.f, recoilForce * 10.f);
				playerObject->ApplyRecoil(recoil);
			}
			else
			{
				recoil = b2Vec2(recoilForce * -10.f, 0.f);
				playerObject->ApplyRecoil(recoil);
			}
		}
		else if ((int)playerFacingVector->x == 0)
		{
			if ((int)playerFacingVector->y > 0)
			{
				recoil = b2Vec2(0.f, recoilForce * -10.f);
				playerObject->ApplyRecoil(recoil);
			}
			else if ((int)playerFacingVector->y < 0)
			{
				recoil = b2Vec2(0.f, recoilForce * 10.f);
				playerObject->ApplyRecoil(recoil);
			}
		}
		else
		{

			if ((int)playerFacingVector->y > 0)
			{
				recoil = b2Vec2(recoilForce * 10.f, recoilForce * -10.f);
				playerObject->ApplyRecoil(recoil);
			}
			else if ((int)playerFacingVector->y < 0)
			{
				recoil = b2Vec2(recoilForce * 10.f, recoilForce * 10.f);
				playerObject->ApplyRecoil(recoil);
			}
			else
			{
				recoil = b2Vec2(recoilForce * 10.f, 0.f);
				playerObject->ApplyRecoil(recoil);
			}
		}
		
	}
}

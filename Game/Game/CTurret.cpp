// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
// (c) 2022 Media Design School
//
// File Name: CTurret.cpp
// Description: CTurret declaration file
// Authors: Michael Wai Kit Tran

#include "CTurret.h"
#include "CBullet.h"
#include "CManager.h"
#include "CPlayer.h"
#include "CSound.h"
#include "MathUtils.h"

float CTurret::bulletDamage = 1.0f;
float CTurret::bulletSpeed = 4.0f;
float CTurret::coolDown = 1.0f;
float CTurret::sightDistance = 400.0f;

CTurret::CTurret(sf::Vector2f _pos)
{
	coolDownTimer = coolDown;

	texture = std::make_shared<sf::Texture>();
	texture->loadFromFile("Assets/Sprites/weaponSprites/topDownTurret.png");
	transform.setOrigin(sf::Vector2f(5.0f, 5.0f));
	transform.setPosition(_pos);
	transform.setScale(3.0f, 3.0f);
	drawable = new sf::Sprite(*texture);

	objType = MapPlaceableObjects::Turret;
}

void CTurret::Update()
{
	// get the closest player position
	sf::Vector2f playerPos;
	bool seePlayer = false;
	{
		float closestPlayerDistance = INFINITY;
		for (auto& player : CPlayer::playersInWorld)
		{
			// get the distance between the turret and the player
			float playerDistance = sf::Distance(transform.getPosition(), player->transform.getPosition());
			
			// check whether the player is outside sight distance
			if (playerDistance > CTurret::sightDistance) continue;
			
			// check whether the found player is closer than the previous player found
			if (playerDistance < closestPlayerDistance)
			{
				playerPos = player->transform.getPosition();
				closestPlayerDistance = playerDistance;
				seePlayer = true;
			}
		}
	}
	
	// dont do anything if it does not see a player
	if (!seePlayer) return;

	// face towards closest player
	sf::Vector2f facingDirection = sf::Normalise(playerPos - transform.getPosition());
	transform.setRotation(atan2f(facingDirection.y, facingDirection.x) * 180.0f / PI);

	// update cooldown timer
	coolDownTimer -= GetManager().deltaTime;
	
	// shoot projectile
	if (coolDownTimer <= 0)
	{
		float projectileMomentum = 1.f;
		float projectileRange = 10.f;
		// create and launch projectile
		new CBullet
		(
			bulletDamage, 
			bulletSpeed, 
			projectileMomentum, 
			projectileRange, 
			transform.getPosition(), 
			bulletSpeed * b2Vec2(facingDirection.x, facingDirection.y)
		);
	
		// create sound effect
		(new CSound("gun1.wav"))->SetVolume(10.0f);

		// reset timer
		coolDownTimer = coolDown;
	}
}

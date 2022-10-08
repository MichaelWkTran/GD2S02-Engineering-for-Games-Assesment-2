#include "CTurret.h"
#include "CBullet.h"
#include "CManager.h"
#include "CPlayer.h"
#include "MathUtils.h"

float CTurret::bulletDamage = 1.0f;
float CTurret::bulletSpeed = 4.0f;
float CTurret::coolDown = 1.0f;
float CTurret::sightDistance = 400.0f;

CTurret::CTurret()
{
	coolDownTimer = coolDown;
	
	texture = std::make_shared<sf::Texture>();
	texture->loadFromFile("Assets/Sprites/Goon6.png");

	transform.setOrigin(sf::Vector2f(texture->getSize()) / 2.0f);
	drawable = new sf::Sprite(*texture);

	objType = MapPlaceableObjects::Turret;

}

CTurret::CTurret(sf::Vector2f _pos)
{
	coolDownTimer = coolDown;

	texture = std::make_shared<sf::Texture>();
	texture->loadFromFile("Assets/Sprites/Goon6.png");

	transform.setOrigin(sf::Vector2f(texture->getSize()) / 2.0f);
	transform.setPosition(_pos);
	drawable = new sf::Sprite(*texture);

	objType = MapPlaceableObjects::Turret;
}

CTurret::~CTurret()
{
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

	//Update cooldown timer
	coolDownTimer -= GetManager().deltaTime;
	
	//Shoot projectile
	if (coolDownTimer <= 0)
	{
		//Shoot projectile
		new CBullet
		(
			bulletDamage,
			bulletSpeed,
			transform.getPosition(),
			bulletSpeed * b2Vec2(facingDirection.x, facingDirection.y)
		);
	
		// reset timer
		coolDownTimer = coolDown;
	}
}

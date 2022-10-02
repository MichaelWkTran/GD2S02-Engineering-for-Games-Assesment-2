#include "CTurret.h"
#include "CBullet.h"
#include "CManager.h"
#include "CPlayer.h"

#define PI 3.14159265359

float CTurret::bulletDamage = 0.0f;
float CTurret::bulletSpeed = 0.0f;
float CTurret::coolDown = 0.0f;
float CTurret::sightDistance = 0.0f;

CTurret::CTurret()
{
	coolDownTimer = coolDown;
}

CTurret::~CTurret()
{
}

void CTurret::Update()
{
	// face towards closest player
	sf::Vector2f playerPos;
	{
		float closestPlayerDistance = 0;
		for (auto& player : CPlayer::playersInWorld)
		{
			sf::Vector2f differenceVector = transform.getPosition() - playerPos;
			float playerDistance = sqrtf((differenceVector.x * differenceVector.x) + (differenceVector.y * differenceVector.y));

			if (closestPlayerDistance == 0 || playerDistance < closestPlayerDistance)
			{
				playerPos = differenceVector;
				closestPlayerDistance = playerDistance;
			}
		}
	}
	

	//Update timer
	coolDownTimer -= GetManager().deltatime;

	//Shoot projectile
	if (coolDownTimer <= 0)
	{
		//Shoot projectile
		new CBullet
		(
			bulletDamage,
			bulletSpeed,
			transform.getPosition(),
			bulletSpeed * b2Vec2
			(
				cosf(transform.getRotation() * PI / 180.0f),
				sinf(transform.getRotation() * PI / 180.0f)
			)
		);

		// reset timer
		coolDownTimer = coolDown;
	}
}

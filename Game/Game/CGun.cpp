#include "CGun.h"
#include "CManager.h"
#include "CPlayer.h"
#include "CBullet.h"
#include <iostream>

CGun::CGun(b2Vec2* _playerFaceDirection, CPlayer* _player)
{
	playerFacingDirection = _playerFaceDirection;
	ownerPlayer = _player;

	// setup CGameObject
	float radius = 40.0f;

	transform.setOrigin(sf::Vector2f(radius / 4, radius));

	// setup sf::Drawable
	drawable = new sf::RectangleShape(sf::Vector2f(radius / 2, radius));
	((sf::CircleShape*)drawable)->setFillColor(sf::Color().Black);
	transform.setPosition(ownerPlayer->transform.getPosition());

	switch ((int)playerFacingDirection->x)
	{
	case 0:
		switch ((int)playerFacingDirection->y)
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
		switch ((int)playerFacingDirection->y)
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
		switch ((int)playerFacingDirection->y)
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

CGun::~CGun()
{
}

void CGun::Update()
{
	if (counterFireRate < fireRate)
	{
		counterFireRate += GetManager().deltatime;
	}

	// update the current rotation
	if ((int)playerFacingDirection->x > 0)
	{
		if ((int)playerFacingDirection->y > 0)
		{
			transform.setRotation(135);
		}
		else if ((int)playerFacingDirection->y < 0)
		{
			transform.setRotation(45);
		}
		else
		{
			transform.setRotation(90);
		}
	}
	else if ((int)playerFacingDirection->x == 0)
	{
		if ((int)playerFacingDirection->y > 0)
		{
			transform.setRotation(180);
		}
		else if ((int)playerFacingDirection->y < 0)
		{
			transform.setRotation(0);
		}
	}
	else
	{

		if ((int)playerFacingDirection->y > 0)
		{
			transform.setRotation(-135);
		}
		else if ((int)playerFacingDirection->y < 0)
		{
			transform.setRotation(-45);
		}
		else
		{
			transform.setRotation(-90);
		}
	}

	// update position
	sf::Drawable* playerDrawable = ownerPlayer->GetDrawable();
	transform.setPosition(dynamic_cast<sf::Transformable*>(playerDrawable)->getPosition());
}

void CGun::Shoot()
{
	if (counterFireRate >= fireRate)
	{
		int multiplier = 5;
		sf::Vector2f bulletSpawnPos = sf::Vector2f(dynamic_cast<sf::Transformable*>(drawable)->getPosition().x + playerFacingDirection->x * multiplier, dynamic_cast<sf::Transformable*>(drawable)->getPosition().y + playerFacingDirection->y * multiplier);
		for (int i = 0; i < bulletCount; i++)
		{
			GetManager().objectsInWorld.emplace_back(new CBullet(damage, bulletSpeed, bulletSpawnPos, *playerFacingDirection));
		}
		counterFireRate = 0;
	}
}

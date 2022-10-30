#include "CBullet.h"
#include "CPhysicsBody.h"
#include "CManager.h"
#include "CPlayer.h"
#include "CSound.h"
#include <iostream>

CBullet::CBullet(float _damage, float _moveSpeed, float _momentum, float _projectileRange, sf::Vector2f _spawnPosition, b2Vec2 _velocity)
{
	damage = _damage;
	moveSpeed = _moveSpeed;
	velocity = _velocity;
	projectileMomentum = _momentum;
	projectileRange = _projectileRange;

	velocity *= moveSpeed;

	tags.emplace("Bullet");

	// setup CGameObject
	float radius = 4.0f;

	// set the origin of the SFML transform
	transform.setOrigin(radius, radius);

	// setup sf::Drawable
	drawable = new sf::CircleShape(radius);
	((sf::CircleShape*)drawable)->setFillColor(sf::Color().Blue);
	transform.setPosition(_spawnPosition);

	// setup b2BodyDef
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.bullet = true;
	bodyDef.position = GetManager().pixelToWorldScale * b2Vec2(transform.getPosition().x, transform.getPosition().y);

	// setup b2Shape
	b2CircleShape shape;
	shape.m_radius = radius * GetManager().pixelToWorldScale;

	// setup b2FixtureDef
	b2FixtureDef fixtureDef;
	fixtureDef.density = projectileMomentum;
	fixtureDef.shape = &shape;

	// setup b2Body
	SetupBody(bodyDef, &fixtureDef, 1);
}

void CBullet::Update()
{
	projectileRange -= GetManager().deltaTime;
	if (projectileRange < 0)
	{
		DeleteObject();
	}
	body->SetLinearVelocity(velocity);
}

void CBullet::BeginContact(CPhysicsBody* _other)
{
	// collision with player
	{
		CPlayer* player = dynamic_cast<CPlayer*>(_other);
		if (player)
		{
			// damage player 1 if shot by a bullet from player 2
			if (TagExists("Player2"))
			{
				if (player->isPlayerOne) { player->TakeDamage(damage); DeleteObject(); new CSound("playerHit.wav"); }	
			}
			// damage player 2 if shot by a bullet from player 1
			else if (TagExists("Player1"))
			{
				if (!player->isPlayerOne) { player->TakeDamage(damage); DeleteObject(); new CSound("playerHit.wav"); }
			}
			// damage both player 1 and 2 if it is from neither player 1 or 2
			else
			{
				player->TakeDamage(damage);
				DeleteObject();
				new CSound("playerHit.wav");
			}
		}
	}
	
	// collision with wall
	{
		CWall* wall = dynamic_cast<CWall*>(_other);
		if (wall) DeleteObject();

		// play hit sound
		(new CSound("bulletHit.wav"))->SetVolume(20.0f);
	}
}
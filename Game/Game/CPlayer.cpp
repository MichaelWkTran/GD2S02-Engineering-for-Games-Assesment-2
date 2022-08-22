#include "CPlayer.h"
#include "CManager.h"
#include "CPhysicsBody.h"
#include "CBullet.h"
#include "CGun.h"
#include <iostream>

CPlayer::CPlayer(sf::Keyboard::Key _up, sf::Keyboard::Key _down, sf::Keyboard::Key _left, sf::Keyboard::Key _right, sf::Keyboard::Key _shoot, sf::Vector2f _spawnPos)
{
    up = _up;
    down = _down;
    left = _left;
    right = _right;
    shoot = _shoot;

    maxHealth = health = 10.0f;
	moveSpeed = 6.0f;
	coolDown = 0.0f;

    tags.emplace("Player");

    // setup CGameObject
	float radius = 16.0f;

    // set the origin of the SFML transform
	transform.setOrigin(sf::Vector2f(radius, radius));

    // setup sf::Drawable
	drawable = new sf::RectangleShape(sf::Vector2f(radius, radius) * 2.0f);
	((sf::RectangleShape*)drawable)->setFillColor(sf::Color().Red);
	transform.setPosition(_spawnPos);

    // setup b2BodyDef
    physicsBody = new CPhysicsBody;
    physicsBody->bodyDef.type = b2_dynamicBody;

    // setup b2Shape
    physicsBody->SetupShape<b2CircleShape>();
    physicsBody->GetShape().m_radius = radius * GetManager().pixelToWorldScale;
    physicsBody->bodyDef.position = b2Vec2(transform.getPosition().x * GetManager().pixelToWorldScale, transform.getPosition().y * GetManager().pixelToWorldScale);

    // setup b2FixtureDef
    physicsBody->fixtureDef.density = 1.0f;

    // setup b2Body
    physicsBody->SetupBody();
    physicsBody->GetBody().SetFixedRotation(true);

    facingDirection = b2Vec2(1, 0);
    heldGun = new CGun(&facingDirection, this);
}

CPlayer::~CPlayer()
{
}

void CPlayer::Update()
{
    // player movement
    b2Vec2 movement = b2Vec2
    (
        sf::Keyboard::isKeyPressed(right) - sf::Keyboard::isKeyPressed(left), 
        sf::Keyboard::isKeyPressed(down) - sf::Keyboard::isKeyPressed(up)
    );
    movement.Normalize();
    movement *= moveSpeed;
    
    physicsBody->GetBody().SetLinearVelocity(movement);
    
    if (movement != b2Vec2(0, 0))
    {
        facingDirection = b2Vec2(movement.x, movement.y);
    }

    // cap player health
    if (health > maxHealth) health = maxHealth;
    
    // player death
    if (health < 0.0f) DeleteObject();

    if (sf::Keyboard::isKeyPressed(shoot))
    {
        heldGun->Shoot();
    }
}

void CPlayer::AddGunToRender()
{
    GetManager().objectsInWorld.push_back(heldGun);
}

void CPlayer::TakeDamage(float _damage)
{
    health -= _damage;
}

#include "CPlayer.h"
#include "CManager.h"
#include "CPhysicsBody.h"
#include "CBullet.h"
#include <iostream>

CPlayer::CPlayer()
{
    maxHealth = health = 100.0f;
	moveSpeed = 6.0f;
	coolDown = 0.0f;

    // setup CGameObject
	float radius = 16.0f;

    // set the origin of the SFML transform
	transform.setOrigin(sf::Vector2f(radius, radius));

    // setup sf::Drawable
	drawable = new sf::RectangleShape(sf::Vector2f(radius, radius) * 2.0f);
	((sf::RectangleShape*)drawable)->setFillColor(sf::Color().Red);

    // setup b2BodyDef
    physicsBody = new CPhysicsBody;
    physicsBody->bodyDef.type = b2_dynamicBody;

    // setup b2Shape
    physicsBody->SetupShape<b2CircleShape>();
    physicsBody->GetShape().m_radius = radius * GetManager().pixelToWorldScale;

    // setup b2FixtureDef
    physicsBody->fixtureDef.density = 1.0f;

    // setup b2Body
    physicsBody->SetupBody();
}

CPlayer::~CPlayer()
{
}

void CPlayer::Update()
{
    // player movement
    b2Vec2 movement = b2Vec2
    (
        sf::Keyboard::isKeyPressed(sf::Keyboard::Right) - sf::Keyboard::isKeyPressed(sf::Keyboard::Left), 
        sf::Keyboard::isKeyPressed(sf::Keyboard::Down) - sf::Keyboard::isKeyPressed(sf::Keyboard::Up)
    );
    movement.Normalize();
    movement *= moveSpeed;
    
    physicsBody->GetBody().SetLinearVelocity(movement);

    // cap player health
    if (health > maxHealth) health = maxHealth;
    
    // player death
    if (health < 0.0f) DeleteObject();

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        CBullet* bullet = new CBullet(1, 0, dynamic_cast<sf::Transformable*>(drawable)->getPosition());
        GetManager().objectsInWorld.emplace_back(new CBullet(1, 10, dynamic_cast<sf::Transformable*>(drawable)->getPosition()));
    }
}

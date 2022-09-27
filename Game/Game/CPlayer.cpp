#include "CPlayer.h"
#include "CManager.h"
#include "CPhysicsBody.h"
#include "CBullet.h"
#include "CGun.h"
#include <iostream>

CPlayer::CPlayer(sf::Keyboard::Key _up, sf::Keyboard::Key _down, sf::Keyboard::Key _left, sf::Keyboard::Key _right, sf::Keyboard::Key _shoot, sf::Vector2f _spawnPos, bool _isPlayerOne)
{
    up = _up;
    down = _down;
    left = _left;
    right = _right;
    shoot = _shoot;
    isPlayerOne = _isPlayerOne;

    maxHealth = health = 10.0f;
	moveSpeed = 6.0f;
	coolDown = 0.0f;

    tags.emplace("Player");

    // setup CGameObject
	float radius = 16.0f;

    // set the origin of the SFML transform
	transform.setOrigin(radius, radius);

    // setup sf::Drawable
	drawable = new sf::RectangleShape(sf::Vector2f(radius, radius) * 2.0f);
	((sf::RectangleShape*)drawable)->setFillColor(sf::Color().Red);
	transform.setPosition(_spawnPos);

    // setup b2BodyDef
    physicsBody = new CPhysicsBody;
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.fixedRotation = true;
    bodyDef.position = GetManager().pixelToWorldScale * b2Vec2(transform.getPosition().x, transform.getPosition().y);

    // setup b2Shape
    b2CircleShape shape;
    shape.m_radius = radius * GetManager().pixelToWorldScale;

    // setup b2FixtureDef
    b2FixtureDef fixtureDef;
    fixtureDef.density = 1.0f;
    fixtureDef.shape = &shape;

    // setup b2Body
    physicsBody->SetupBody(bodyDef, &fixtureDef, 1);
    physicsBody->GetBody().GetUserData().pointer = reinterpret_cast<uintptr_t>(this);

    facingDirection = b2Vec2(1, 0);
    heldGun = new CGun(&facingDirection, this);

    if (isPlayerOne)
    {
        healthString = "Player One Health: " + std::to_string(health);
        healthText.setPosition({ 10, 10 });
    }
    else
    {
        healthString = "Player Two Health: " + std::to_string(health);
        healthText.setPosition({ 1000, 10 });
    }
    healthText.setString(healthString);
    healthText.setFillColor(sf::Color::Black);
    healthText.setFont(GetManager().font);
    healthText.setCharacterSize(20);
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

    // shoot projectile
    if (sf::Keyboard::isKeyPressed(shoot))
    {
        heldGun->Shoot();
    }
}

void CPlayer::AddGunToRender()
{
    //GetManager().objectsInWorld.push_back(heldGun);
}

void CPlayer::TakeDamage(float _damage)
{
    health -= _damage;
    if (isPlayerOne)
    {
        healthString = "Player One Health: " + std::to_string(health);
    }
    else
    {
        healthString = "Player Two Health: " + std::to_string(health);
    }
    healthText.setString(healthString);

    // player death
    if (health <= 0.0f)
    {
        DeleteObject();
        heldGun->DeleteObject();
        heldGun->ownerPlayer = nullptr;
    }
}

void CPlayer::Draw()
{
    if (!visible) return;

    // transform the drawable to m_Transfrom
    sf::Transformable* drawableTransform = dynamic_cast<sf::Transformable*>(drawable);
    if (drawableTransform == nullptr)
    {
        std::cout << "ERROR: m_pDrawable in CGameObject must inherit from sf::Transformable\n";
        return;
    }

    drawableTransform->setPosition(transform.getPosition());
    drawableTransform->setScale(transform.getScale());
    drawableTransform->setRotation(transform.getRotation());
    drawableTransform->setOrigin(transform.getOrigin());

    // draw drawable
    GetManager().GetWindow().draw(*drawable);

    GetManager().GetWindow().draw(healthText);
}

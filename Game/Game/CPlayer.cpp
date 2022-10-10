// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
// (c) 2022 Media Design School
//
// File Name: CPlayer.cpp
// Description: CPlayer declaration file
// Authors: Michael Wai Kit Tran

#include "CPlayer.h"
#include "CManager.h"
#include "CPhysicsBody.h"
#include "CBullet.h"
#include "CGun.h"
#include "CWeapons.h"
#include "CHealthBar.h"
#include "CGameObject.h"
#include "CUpdatedObject.h"
#include "CWeaponUI.h"
#include <iostream>

#include "WinScene.h"

std::set<CPlayer*> CPlayer::playersInWorld;

int WinScene::playerOneScore = 0;
int WinScene::playerTwoScore = 0;

bool WinScene::playerOneRoundWin = false;
bool WinScene::playerTwoRoundWin = false;

CPlayer::CPlayer(sf::Keyboard::Key _up, sf::Keyboard::Key _down, sf::Keyboard::Key _left, sf::Keyboard::Key _right, sf::Keyboard::Key _shoot, sf::Vector2f _spawnPos, bool _isPlayerOne)
{
    WinScene::playerOneRoundWin = false; // resets when new player is created
    WinScene::playerTwoRoundWin = false; // resets when new player is created

    playersInWorld.insert(this);

    up = _up;
    down = _down;
    left = _left;
    right = _right;
    shoot = _shoot;
    isPlayerOne = _isPlayerOne;

    heldWeaponInt = 0;

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
    SetupBody(bodyDef, &fixtureDef, 1);
    body->GetUserData().pointer = reinterpret_cast<uintptr_t>(this);

    facingDirection = b2Vec2(1, 0);
    //heldGun = new CGun(&facingDirection, this);
    heldWeapon = new CWeapons(&facingDirection, this, heldWeaponInt);

    if (isPlayerOne)
    {
        healthString = "Player One Health: " + std::to_string(health);
        healthText.setPosition({ 10, 10 });
        playerHealthBar = new CHealthBar(sf::Vector2f(5.f, 625.f), this);
        playerWeaponUI = new CWeaponUI(sf::Vector2f(0.f, 645.f), sf::Vector2f(5.f, 655.f), sf::Vector2f(10.f, 695.f), this);
    }
    else
    {
        healthString = "Player Two Health: " + std::to_string(health);
        healthText.setPosition({ 1000, 10 });
        playerHealthBar = new CHealthBar(sf::Vector2f(1125.f, 625.f), this);
        playerWeaponUI = new CWeaponUI(sf::Vector2f(1125.f, 645.f), sf::Vector2f(1130.f, 655.f), sf::Vector2f(1135.f, 695.f), this);
    }
    healthText.setString(healthString);
    healthText.setFillColor(sf::Color::Black);
    healthText.setFont(GetManager().font);
    healthText.setCharacterSize(20);

}

CPlayer::~CPlayer()
{
    playersInWorld.erase(this);
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
    if (movement.x > 6) { movement.x = 6; }
    if (movement.y > 6) { movement.y = 6; }
    
    
    //body->SetLinearVelocity(movement);
    body->ApplyForceToCenter(movement, true);
    body->SetLinearDamping(8.f);
    if (movement != b2Vec2(0, 0))
    {
        facingDirection = b2Vec2(movement.x, movement.y);
    }

    // cap player health
    if (health > maxHealth) health = maxHealth;

    // shoot projectile
    if (sf::Keyboard::isKeyPressed(shoot))
    {
        //heldGun->Shoot();
        heldWeapon->Shoot();
        
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
        //heldGun->DeleteObject();
        //heldGun->ownerPlayer = nullptr;
        heldWeapon->DeleteObject();
        heldWeapon->playerObject = nullptr;

        if (isPlayerOne)
        {
            WinScene::playerTwoScore++;
            WinScene::playerTwoRoundWin = true;
        }
        else
        {
            WinScene::playerOneScore++;
            WinScene::playerOneRoundWin = true;
        }
    }
}

void CPlayer::NewWeapon(int _heldWeaponInt)
{
    heldWeapon->DeleteObject();
    heldWeapon = new CWeapons(&facingDirection, this, _heldWeaponInt);
    heldWeaponInt = _heldWeaponInt;
    // play weapon pickup sound
}

void CPlayer::ApplyRecoil(b2Vec2 _recoil)
{
    body->ApplyLinearImpulseToCenter(_recoil, false);
}

void CPlayer::Draw()
{
    if (!visible) return;

    // transform the drawable to m_Transfrom
    sf::Transformable* drawableTransform = dynamic_cast<sf::Transformable*>(drawable);
    if (drawableTransform == nullptr)
    {
        std::cout << "ERROR: _Drawable in CGameObject must inherit from sf::Transformable\n";
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

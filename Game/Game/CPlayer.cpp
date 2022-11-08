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
#include "CLevelMaker.h"
#include <iostream>
#include "CSound.h"

#include "CWinScene.h"

std::set<CPlayer*> CPlayer::playersInWorld;

int CWinScene::playerOneScore = 0;
int CWinScene::playerTwoScore = 0;

bool CWinScene::playerOneRoundWin = false;
bool CWinScene::playerTwoRoundWin = false;

CPlayer::CPlayer(sf::Keyboard::Key _up, sf::Keyboard::Key _down, sf::Keyboard::Key _left, sf::Keyboard::Key _right, sf::Keyboard::Key _shoot, sf::Vector2f _spawnPos, bool _isPlayerOne)
{
    CWinScene::playerOneRoundWin = false; // resets when new player is created
    CWinScene::playerTwoRoundWin = false; // resets when new player is created

    playersInWorld.insert(this);

    up = _up;
    down = _down;
    left = _left;
    right = _right;
    shoot = _shoot;
    isPlayerOne = _isPlayerOne;

    heldWeaponInt = 0;

    maxHealth = health = 10.0f;
	moveSpeed = 30.0f;
	coolDown = 0.0f;

    tags.emplace("Player");

    texRect = sf::IntRect(0, 0, 48, 48);

    // setup CGameObject
	float radius = 14.0f;

    // set the origin of the SFML transform
	transform.setOrigin(radius, radius);

    //player sprite scale
    int temp = 50;

    // setup sf::Drawable
	drawable = new sf::RectangleShape(sf::Vector2f(temp, temp));
	((sf::RectangleShape*)drawable)->setFillColor(sf::Color().White);
    //((sf::RectangleShape*)drawable)->setPosition(sf::Vector2f(((sf::RectangleShape*)drawable)->getPosition().x - 30, ((sf::RectangleShape*)drawable)->getPosition().y - 30));
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

    facingDirection = b2Vec2(1, 0);
    //heldGun = new CGun(&facingDirection, this);
    heldWeapon = new CWeapons(&facingDirection, this, heldWeaponInt);

    if (isPlayerOne)
    {
        playerHealthBar = new CHealthBar(sf::Vector2f(5.f, 625.f), this);
        playerWeaponUI = new CWeaponUI(sf::Vector2f(0.f, 645.f), sf::Vector2f(5.f, 655.f), sf::Vector2f(10.f, 695.f), this);
        playerTex.loadFromFile("Assets/Sprites/playerSprites/playerBlueSprite.png");
    }
    else
    {
        playerHealthBar = new CHealthBar(sf::Vector2f(1125.f, 625.f), this);
        playerWeaponUI = new CWeaponUI(sf::Vector2f(1125.f, 645.f), sf::Vector2f(1130.f, 655.f), sf::Vector2f(1135.f, 695.f), this);
        playerTex.loadFromFile("Assets/Sprites/playerSprites/playerRedSprite.png");
    }
    ((sf::RectangleShape*)drawable)->setTexture(&playerTex);
    ((sf::RectangleShape*)drawable)->setTextureRect(texRect);
}

CPlayer::~CPlayer()
{
    playersInWorld.erase(this);
}

void CPlayer::Update()
{
    // cap player health
    if (health > maxHealth) health = maxHealth;

    // shoot projectile
    if (sf::Keyboard::isKeyPressed(shoot))
    {
        //heldGun->Shoot();
        heldWeapon->Shoot();
        
    }

    if (CWinScene::playerOneRoundWin || CWinScene::playerTwoRoundWin)
    {
        Kill();
    }
}

void CPlayer::FixedUpdate()
{
    // player movement
    b2Vec2 movement = b2Vec2
    (
        (float)(sf::Keyboard::isKeyPressed(right) - sf::Keyboard::isKeyPressed(left)),
        (float)(sf::Keyboard::isKeyPressed(down) - sf::Keyboard::isKeyPressed(up))
    );

    if (movement != b2Vec2(0, 0)) { facingDirection = b2Vec2(movement.x, movement.y); }

    movement.Normalize();
    movement *= moveSpeed;
    if (movement.x > moveSpeed) { movement.x = moveSpeed; }
    if (movement.y > moveSpeed) { movement.y = moveSpeed; }

    //body->SetLinearVelocity(movement);
    body->ApplyForceToCenter(movement, true);
    body->SetLinearDamping(8.f);

    //animation
    if (movement.x > 0)
    {
        if (animClock.getElapsedTime().asSeconds() > 0.3f)
        {
            texRect.left = 144;
            if (texRect.top == 144)
            {
                texRect.top = 0;
            }
            else
            {
                texRect.top += 48;
            }
            ((sf::RectangleShape*)drawable)->setTextureRect(texRect);
            animClock.restart();
        }
    }
    else if (movement.x < 0)
    {
        if (animClock.getElapsedTime().asSeconds() > 0.3f)
        {
            texRect.left = 48;
            if (texRect.top == 144)
            {
                texRect.top = 0;
            }
            else
            {
                texRect.top += 48;
            }
            ((sf::RectangleShape*)drawable)->setTextureRect(texRect);
            animClock.restart();
        }
    }
    else if (movement.x == 0)
    {
        if (movement.y > 0)
        {
            if (animClock.getElapsedTime().asSeconds() > 0.3f)
            {
                texRect.left = 0;
                if (texRect.top == 144)
                {
                    texRect.top = 0;
                }
                else
                {
                    texRect.top += 48;
                }
                ((sf::RectangleShape*)drawable)->setTextureRect(texRect);
                animClock.restart();
            }
        }
        else if (movement.y < 0)
        {
            if (animClock.getElapsedTime().asSeconds() > 0.3f)
            {
                texRect.left = 96;
                if (texRect.top == 144)
                {
                    texRect.top = 0;
                }
                else
                {
                    texRect.top += 48;
                }
                ((sf::RectangleShape*)drawable)->setTextureRect(texRect);
                animClock.restart();
            }
        }

    }
    else if (movement.y == 0 && movement.x == 0)
    {
        if (animClock.getElapsedTime().asSeconds() > 0.3f)
        {
            texRect.left = 192;
            if (texRect.top == 48)
            {
                texRect.top = 0;
            }
            else
            {
                texRect.top += 48;
            }
        }
    }
    else
    {
        texRect.top = 0;
        texRect.left = 0;
        ((sf::RectangleShape*)drawable)->setTextureRect(texRect);
    }
}

void CPlayer::AddGunToRender()
{
    //GetManager().objectsInWorld.push_back(heldGun);
}

void CPlayer::TakeDamage(float _damage)
{
    health -= _damage;

    // player death
    if (health <= 0.0f)
    {
        GetManager().SetPlayerReferanceNull(this);
        GetManager().spawnWeapons = false;
        DeleteObject();
        GetManager().levelMaker->CleanUp();
        //heldGun->DeleteObject();
        //heldGun->ownerPlayer = nullptr;
        heldWeapon->DeleteObject();
        heldWeapon->playerObject = nullptr;

        if (isPlayerOne)
        {
            CWinScene::playerTwoScore++;
            CWinScene::playerTwoRoundWin = true;
        }
        else
        {
            CWinScene::playerOneScore++;
            CWinScene::playerOneRoundWin = true;
        }
    }
}

void CPlayer::Kill()
{
    GetManager().SetPlayerReferanceNull(this);
    GetManager().spawnWeapons = false;
    DeleteObject();

    playerHealthBar->DeleteObject();
    playerHealthBar = nullptr;

    playerWeaponUI->DeleteObject();
    playerWeaponUI = nullptr;

    heldWeapon->DeleteObject();
    heldWeapon->playerObject = nullptr;
}

void CPlayer::NewWeapon(int _heldWeaponInt)
{
    if (heldWeaponInt == _heldWeaponInt)
    {
        _heldWeaponInt += 1;
        if (_heldWeaponInt >= 4)
        {
            _heldWeaponInt = 0;
        }
    }
    heldWeapon->DeleteObject();
    heldWeapon = new CWeapons(&facingDirection, this, _heldWeaponInt);
    heldWeaponInt = _heldWeaponInt;
    // play weapon pickup sound
    new CSound("gunPickup.wav");
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

    drawableTransform->setPosition(transform.getPosition().x - 12, transform.getPosition().y - 17);
    drawableTransform->setScale(transform.getScale());
    drawableTransform->setRotation(transform.getRotation());
    drawableTransform->setOrigin(transform.getOrigin());

    // draw drawable
    GetManager().GetWindow().draw(*drawable);

    //GetManager().GetWindow().draw(healthText);
}

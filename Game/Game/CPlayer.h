// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
// (c) 2022 Media Design School
//
// File Name: CPlayer.h
// Description: CPlayer initialization file
// Authors: Michael Wai Kit Tran

#pragma once
#include "CGameObject.h"
#include "CPhysicsBody.h"
#include <set>

class CGun;
class CWeapons;
class CHealthBar;
class CWeaponUI;

class CPlayer : public CPhysicsBody, public CGameObject
{
private:
	sf::Texture playerTex;
	sf::IntRect texRect;
	sf::Clock animClock;

public:
	static std::set<CPlayer*> playersInWorld;

	float maxHealth;
	float moveSpeed;
	float coolDown;
	bool isPlayerOne;
	b2Vec2 facingDirection;
	//CGun* heldGun = nullptr;
	CWeapons* heldWeapon = nullptr;
	int heldWeaponInt;

	CHealthBar* playerHealthBar = nullptr;
	CWeaponUI* playerWeaponUI = nullptr;

	// input variables
	sf::Keyboard::Key up;
	sf::Keyboard::Key down;
	sf::Keyboard::Key left;
	sf::Keyboard::Key right;
	sf::Keyboard::Key shoot;

	// health info
	sf::Text healthText;
	sf::String healthString;
	float health;

	CPlayer(sf::Keyboard::Key _up, sf::Keyboard::Key _down, sf::Keyboard::Key _left, sf::Keyboard::Key _right, sf::Keyboard::Key _shoot, sf::Vector2f _spawnPos, bool _isPlayerOne);
	~CPlayer();

	void SetPosition(sf::Vector2f _pos);

	virtual void Update() override;
	void AddGunToRender();

	void TakeDamage(float _damage);
	void Kill();
	void NewWeapon(int _heldWeaponInt);
	void ApplyRecoil(b2Vec2 _recoil);

	virtual void Draw() override;
};
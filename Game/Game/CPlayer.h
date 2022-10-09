#pragma once
#include "CGameObject.h"
#include "CPhysicsBody.h"
//#include "CWeapons.h"
#include <set>

class CGun;
class CWeapons;

class CPlayer : public CPhysicsBody, public CGameObject
{
public:
	static std::set<CPlayer*> playersInWorld;

	int maxHealth;
	float moveSpeed;
	float coolDown;
	bool isPlayerOne;
	b2Vec2 facingDirection;
	//CGun* heldGun = nullptr;
	CWeapons* heldWeapon = nullptr;
	int heldWeaponInt;
	

	// input variables
	sf::Keyboard::Key up;
	sf::Keyboard::Key down;
	sf::Keyboard::Key left;
	sf::Keyboard::Key right;
	sf::Keyboard::Key shoot;

	// health info
	sf::Text healthText;
	sf::String healthString;
	int health;

	CPlayer(sf::Keyboard::Key _up, sf::Keyboard::Key _down, sf::Keyboard::Key _left, sf::Keyboard::Key _right, sf::Keyboard::Key _shoot, sf::Vector2f _spawnPos, bool _isPlayerOne);
	~CPlayer();

	virtual void Update() override;
	void AddGunToRender();

	void TakeDamage(float _damage);

	virtual void Draw() override;
};
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
// (c) 2022 Media Design School
//
// File Name : CWeaponBox.cpp
// Description: methods of CWeaponBox class
// Authors: Lucas Manssen

#include "CWeaponBox.h"
#include "CManager.h"
#include "CPlayer.h"
#include <iostream>

// class constructor
CWeaponBox::CWeaponBox(sf::Vector2f _spawnPosition)
{
	// randomize weapon contained (reminder: 0 = pistol, 1 = rifle, 2 = sniper, 3 = shotgun)
	time_t t;
	srand((unsigned) time(&t));
	weaponInt = rand() % 4;

	// set up misc attributes
	weaponBoxUsed = false;
	respawnTimer = 30.f;
	respawnTimerCounter = 0.0f;

	// set up rectangle shapes
	boxSize.x = 25.f;
	boxSize.y = 25.f;
	sf::Vector2f tempBoxSize;
	tempBoxSize.x = boxSize.x * 0.75f;
	tempBoxSize.y = boxSize.y * 0.75f;

	boxRect.setFillColor(sf::Color::White);
	boxDesign.setFillColor(sf::Color::Black);

	boxRect.setOutlineColor(sf::Color::Black);
	boxDesign.setOutlineColor(sf::Color::Black);

	boxRect.setOutlineThickness(1.0f);
	boxDesign.setOutlineThickness(1.0f);

	boxRect.setPosition(_spawnPosition);
	boxRect.setOrigin(boxSize.x / 2, boxSize.y / 2);

	boxDesign.setPosition(boxRect.getPosition());
	boxDesign.setOrigin(tempBoxSize.x / 2, tempBoxSize.y / 2);

	boxRect.setSize(boxSize);
	boxDesign.setSize(tempBoxSize);

	// change color based on current weapon
	if (weaponInt == 0)
	{
		// if pistol
		boxDesign.setFillColor(sf::Color::Red);
	}
	if (weaponInt == 1)
	{
		// if rifle
		boxDesign.setFillColor(sf::Color::Yellow);
	}
	if (weaponInt == 2)
	{
		// if sniper
		boxDesign.setFillColor(sf::Color::Green);
	}
	if (weaponInt == 3)
	{
		// if shotgun
		boxDesign.setFillColor(sf::Color::Magenta);
	}

	// load and set textures
	//boxRectTexture.loadFromFile("");
	//boxDesignTexture.loadFromFile("");

	//boxRect.setTexture(&boxRectTexture);
	//boxDesign.setTexture(&boxDesignTexture);

	//boxUsedTexture.loadFromFile("");
	
	// setup b2BodyDef
	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;
	bodyDef.position = GetManager().pixelToWorldScale * b2Vec2(boxRect.getPosition().x, boxRect.getPosition().y);

	// setup b2CircleShape
	b2CircleShape shape;
	shape.m_radius = 13.f * GetManager().pixelToWorldScale;

	// setup b2FixtureDef
	b2FixtureDef fixtureDef;
	fixtureDef.isSensor = true;
	fixtureDef.density = 1.0f;
	fixtureDef.shape = &shape;

	// setup b2Body
	SetupBody(bodyDef, &fixtureDef, 1);

	tags.emplace("WeaponBox");
}

CWeaponBox::~CWeaponBox()
{
}

// if weapon randomization at initialization is undesired
void CWeaponBox::SetWeapon(int _weaponInt)
{
	weaponInt = _weaponInt;
}

// set box unavailable to use, until respawn
void CWeaponBox::SetUsed()
{
	//boxRect.setTexture(&boxUsedTexture);
	//boxDesign.setTexture(&boxUsedTexture);
	weaponBoxUsed = true;
}

// set box available to be used again/respawn
void CWeaponBox::SetUnused()
{
	//boxRect.setTexture(&boxRectTexture);
	//boxDesign.setTexture(&boxDesignTexture);
	weaponBoxUsed = false;
}

// rotate boxes, count down until respawn, adjust color appropriately
void CWeaponBox::Update()
{
	respawnTimerCounter += GetManager().deltaTime;

	boxRect.rotate(0.05f);
	boxDesign.rotate(0.05f);
	if (weaponBoxUsed == false)
	{
		if (weaponInt == 0)
		{
			// if pistol
			boxDesign.setFillColor(sf::Color::Red);
		}
		if (weaponInt == 1)
		{
			// if rifle
			boxDesign.setFillColor(sf::Color::Yellow);
		}
		if (weaponInt == 2)
		{
			// if sniper
			boxDesign.setFillColor(sf::Color::Green);
		}
		if (weaponInt == 3)
		{
			// if shotgun
			boxDesign.setFillColor(sf::Color::Magenta);
		}
	}
	else
	{
		boxDesign.setFillColor(sf::Color(102, 106, 112));
	}

	if (respawnTimerCounter >= respawnTimer)
	{
		respawnTimerCounter = 0.0f;
		SetUnused();
	}
}

// display boxes to frame
void CWeaponBox::Draw()
{
	sf::Transformable* drawableTransform = dynamic_cast<sf::Transformable*>(&boxRect);
	if (drawableTransform == nullptr)
	{
		std::cout << "ERROR: m_Drawable in CGameObject must inherit from sf::Transformable\n";
		return;
	}
	sf::Transformable* drawableTransform2 = dynamic_cast<sf::Transformable*>(&boxDesign);
	if (drawableTransform2 == nullptr)
	{
		std::cout << "ERROR: m_Drawable in CGameObject must inherit from sf::Transformable\n";
		return;
	}

	GetManager().GetWindow().draw(boxRect);
	GetManager().GetWindow().draw(boxDesign);
}

// detect collision with player to toggle usability and give player new weapon
void CWeaponBox::BeginContact(CPhysicsBody* _other)
{
	CPlayer* tempPlayer = dynamic_cast<CPlayer*>(_other);
	if (tempPlayer != nullptr)
	{
		
		if (weaponBoxUsed == false)
		{
			tempPlayer->NewWeapon(weaponInt);
		}
		SetUsed();
		
	}
	
}

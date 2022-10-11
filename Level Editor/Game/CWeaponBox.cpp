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
#include <iostream>

// class constructor
CWeaponBox::CWeaponBox(sf::Vector2f _spawnPosition)
{
	// randomize weapon contained (reminder: 0 = pistol, 1 = rifle, 2 = sniper, 3 = shotgun)
	srand(time(0));
	weaponInt = rand() % 4;

	// set up misc attributes
	weaponBoxUsed = false;
	respawnTimer = 20.f;
	respawnTimerCounter = 0.0f;

	// set up rectangle shapes
	boxSize.x = 4.f;
	boxSize.y = 4.f;
	sf::Vector2f tempBoxSize;
	tempBoxSize.x = boxSize.x * 0.75f;
	tempBoxSize.y = boxSize.y * 0.75f;

	boxRect.setFillColor(sf::Color::White);
	boxDesign.setFillColor(sf::Color::White);

	boxRect.setOutlineColor(sf::Color::Black);
	boxDesign.setOutlineColor(sf::Color::Black);

	boxRect.setOutlineThickness(0.1f);
	boxDesign.setOutlineThickness(0.1f);

	boxRect.setPosition(_spawnPosition);
	boxRect.setOrigin(boxSize.x / 2, boxSize.y / 2);

	boxDesign.setPosition(sf::Vector2f(boxSize.x / 2, boxSize.y / 2));
	boxDesign.setOrigin(tempBoxSize.x / 2, tempBoxSize.y / 2);

	boxRect.setSize(boxSize);
	boxDesign.setSize(tempBoxSize);

	// load and set textures
	//boxRectTexture.loadFromFile("");
	//boxDesignTexture.loadFromFile("");

	//boxRect.setTexture(&boxRectTexture);
	//boxDesign.setTexture(&boxDesignTexture);

	//boxUsedTexture.loadFromFile("");

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

// rotate boxes, count down until respawn
void CWeaponBox::Update()
{
	respawnTimerCounter += GetManager().deltatime;

	boxRect.rotate(0.5);
	boxDesign.rotate(0.5);

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

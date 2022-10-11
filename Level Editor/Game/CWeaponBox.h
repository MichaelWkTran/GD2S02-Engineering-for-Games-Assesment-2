// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
// (c) 2022 Media Design School
//
// File Name : CWeaponBox.h
// Description: header file for CWeaponBox class
// Authors: Lucas Manssen

#pragma once
#include "CGameObject.h"
class CWeaponBox : public CGameObject
{
private:
	int weaponInt = -1;

	sf::RectangleShape boxRect;
	sf::RectangleShape boxDesign;
	sf::Texture boxRectTexture;
	sf::Texture boxDesignTexture;

	sf::Texture boxUsedTexture;

	sf::Vector2f boxSize;

	float respawnTimer;
	float respawnTimerCounter;

public:
	bool weaponBoxUsed;

	CWeaponBox(sf::Vector2f _spawnPosition);
	~CWeaponBox();

	void SetWeapon(int _weaponInt);
	void SetUsed();
	void SetUnused();
	void Update();
	void Draw();
};
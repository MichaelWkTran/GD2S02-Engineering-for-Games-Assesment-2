// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
// (c) 2022 Media Design School
//
// File Name : CHealthBar.h
// Description: Header file for CHealthBar class
// Authors: Lucas Manssen

#pragma once
#include "CGameObject.h"
#include "SFML/Graphics.hpp"
#include "CPlayer.h"
#include "CManager.h"
#include "CUpdatedObject.h"
#include <iostream>

class CHealthBar : public CGameObject
{
private:
	sf::RectangleShape barBackground;
	sf::RectangleShape barFill;

	sf::Vector2f barSize;


	float playerHealth;
	float maxPlayerHealth;

	CPlayer* playerObject = nullptr;

public:
	CHealthBar(sf::Vector2f _barPosition, CPlayer* _player);
	~CHealthBar();
	void Update();
	virtual void Draw() override;
};


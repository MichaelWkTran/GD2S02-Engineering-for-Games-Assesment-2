// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
// (c) 2022 Media Design School
//
// File Name : CWeaponUI.h
// Description: Header file for CWeaponUI class
// Authors: Lucas Manssen

#pragma once
#include "CGameObject.h"
#include "SFML/Graphics.hpp"
#include "CPlayer.h"
#include "CManager.h"
#include "CUpdatedObject.h"
#include <iostream>

class CWeaponUI : public CGameObject
{
private:
	sf::RectangleShape uiIconRect;
	sf::RectangleShape uiBoxRect;

	sf::Text uiText;
	sf::String uiString;

	sf::Texture uiIconTex;

	CPlayer* playerObject = nullptr;

public:
	CWeaponUI(sf::Vector2f _elementPos, sf::Vector2f _iconPos, sf::Vector2f _textPos, CPlayer* _player);
	~CWeaponUI();

	void Update();
	virtual void Draw() override;
};


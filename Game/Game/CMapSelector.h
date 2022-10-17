// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
// (c) 2022 Media Design School
//
// File Name: CMapSelector.h
// Description: CMapSelector header file
// Authors: Sean David Palmer

#pragma once
#include "CManager.h"
#include <SFML/Graphics.hpp>

class CMapSelector : public CGameObject
{
public:
	sf::Vector2f mousePos;

	sf::Transformable buttonTransform[4]; // buttons 
	sf::Transformable backTransform; // back button
	sf::Transformable randTransform; // back button


	CMapSelector();

	void Draw();
	void Update();
	void SetTransformValues(sf::Transformable _transform, sf::Drawable* _drawable);

	static void LoadRandomLevel();

private:
	int buttonHeight;
	int buttonWidth;

	sf::Drawable* buttonDrawable[4];
	sf::Drawable* backDrawable;
	sf::Drawable* randDrawable;

	sf::Text headerText;
	sf::Text buttonText[4];
	sf::Text backText;
	sf::Text randText;
	

	sf::String headerString;
	sf::String buttonString[4];
	sf::String backString;
	sf::String randString;
};


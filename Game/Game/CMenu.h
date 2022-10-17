// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
// (c) 2022 Media Design School
//
// File Name: CMenu.h
// Description: CMenu header file
// Authors: Sean David Palmer

#pragma once
#include "CManager.h"
#include <SFML/Graphics.hpp>

class CMenu : public CGameObject
{
public:
	static bool playGame;
	static bool controlsScreen;
	static bool mapSelectScreen;

	// transform variables
	sf::Transformable bannerTransform; // menu banner
	sf::Transformable playTransform; // play button
	sf::Transformable controlsTransform; // controls button
	sf::Transformable quitTransform; // quit button
	sf::Transformable backTransform; // back button in controls

	sf::Vector2f mousePos;

	CMenu();

	void Draw();
	void Update();
	void SetTransformValues(sf::Transformable _transform, sf::Drawable* _drawable);
	void SetText(sf::Text _text, sf::String _string, float _xPos, float _yPos);
	void CreateDrawable(sf::Drawable* _drawable, sf::Transformable _transformable,
		int _xPos, int _yPos, int _xOrigin, int _yOrigin, int _width, int _height);

private:
	int buttonHeight;
	int buttonWidth;

	sf::Drawable* bannerDrawable;
	sf::Drawable* playDrawable;
	sf::Drawable* controlsDrawable;
	sf::Drawable* quitDrawable;
	sf::Drawable* backDrawable;

	sf::Text playText;
	sf::Text controlsText;
	sf::Text quitText;
	sf::Text backText;

	sf::String playString;
	sf::String controlsString;
	sf::String quitString;
	sf::String backString;


};


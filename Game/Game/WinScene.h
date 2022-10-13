// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
// (c) 2022 Media Design School
//
// File Name: WinScene.h
// Description: WinScene header file
// Authors: Sean David Palmer

#pragma once
#include "CManager.h"
#include <SFML/Graphics.hpp>

class WinScene : public CGameObject
{
public:
	// transform variables
	sf::Transformable restartTransform;

	static int playerOneScore;
	static int playerTwoScore;

	static bool playerOneRoundWin;
	static bool playerTwoRoundWin;

	sf::Vector2f mousePos;

	WinScene();

	void Draw();
	void NextRound();
	void Update();
	void SetTransformValues(sf::Transformable _transform, sf::Drawable* _drawable);

	static sf::Vector2f GetMousePos();


private:
	sf::Text winText;
	sf::String winString;
	sf::String winRoundString;

	sf::Text nextRoundText;
	sf::String nextRoundString;

	// health info
	sf::Text scoreText[2];
	sf::String scoreString[2];

	sf::Drawable* restart;
};


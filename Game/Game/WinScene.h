#pragma once
#include "CManager.h"
#include <SFML/Graphics.hpp>

class WinScene : public CGameObject
{
public:
	sf::Text winText;
	sf::String winString;
	sf::String winRoundString;

	sf::Text nextRoundText;
	sf::String nextRoundString;

	sf::Drawable* restart;

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

	sf::Vector2f GetMousePos();


private:
};


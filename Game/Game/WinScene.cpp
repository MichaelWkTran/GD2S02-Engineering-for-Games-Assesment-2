#include "WinScene.h"
#include "CPlayer.h"
#include <iostream>


WinScene::WinScene()
{
    playerOneScore = 0;
    playerTwoScore = 0;

    playerOneRoundWin = false;
    playerTwoRoundWin = false;

    mousePos = sf::Vector2f(0, 0);

	// setup CGameObject
	float radius = 500.0f;

	// set the origin of the SFML transform
	transform.setOrigin(radius / 2, radius / 2);

	// setup sf::Drawable
	drawable = new sf::RectangleShape(sf::Vector2f(radius, radius));
	((sf::RectangleShape*)drawable)->setFillColor(sf::Color().Blue);
	transform.setPosition(640, 360);

    restart = new sf::RectangleShape(sf::Vector2f(100, 100)); // restart button
	((sf::RectangleShape*)restart)->setFillColor(sf::Color().Red);
    restartTransform.setPosition(640, 450);
    restartTransform.setOrigin(50, 50);
    
    winRoundString = "PLAYER WINS THE ROUND";
    winString = "PLAYER WINS";

    nextRoundString = "NEXT ROUND";

    // text setup
    if (playerOneScore < 2 && playerTwoScore < 2)
    {
        winText.setString(winRoundString); // win round
    }
    else { winText.setString(winString); } // win overall game
    
    winText.setFillColor(sf::Color::Black);
    winText.setFont(GetManager().font);
    winText.setCharacterSize(20);
    winText.setPosition(transform.getPosition().x - 130, transform.getPosition().y - 220);

    nextRoundText.setString(nextRoundString);
    nextRoundText.setFillColor(sf::Color::Black);
    nextRoundText.setFont(GetManager().font);
    nextRoundText.setCharacterSize(12);
    nextRoundText.setPosition(restartTransform.getPosition().x - 40, restartTransform.getPosition().y);
}


void WinScene::Draw()
{
    if (!visible) return;

    // transform the drawable to m_Transfrom
    sf::Transformable* drawableTransform = dynamic_cast<sf::Transformable*>(drawable);
    if (drawableTransform == nullptr)
    {
        std::cout << "ERROR: m_pDrawable in CGameObject must inherit from sf::Transformable\n";
        return;
    }

    // transform the drawable to m_Transfrom
    sf::Transformable* drawableTransform2 = dynamic_cast<sf::Transformable*>(restart);
    if (drawableTransform == nullptr)
    {
        std::cout << "ERROR: m_pDrawable in CGameObject must inherit from sf::Transformable\n";
        return;
    }

    drawableTransform->setPosition(transform.getPosition());
    drawableTransform->setScale(transform.getScale());
    drawableTransform->setRotation(transform.getRotation());
    drawableTransform->setOrigin(transform.getOrigin());

    drawableTransform2->setPosition(restartTransform.getPosition());
    drawableTransform2->setScale(restartTransform.getScale());
    drawableTransform2->setRotation(restartTransform.getRotation());
    drawableTransform2->setOrigin(restartTransform.getOrigin());


    if (playerOneRoundWin || playerTwoRoundWin)
    {
        // draw drawable and text
        GetManager().GetWindow().draw(*drawable);
        GetManager().GetWindow().draw(*restart);
        GetManager().GetWindow().draw(winText);
        GetManager().GetWindow().draw(nextRoundText);
    }

}


void WinScene::NextRound()
{
    if (playerOneRoundWin) // if player one won the game
    {
        // create new player 2 object
        CPlayer* player2 = new CPlayer(sf::Keyboard::Up, sf::Keyboard::Down, sf::Keyboard::Left,
            sf::Keyboard::Right, sf::Keyboard::Slash, { 800, 500 }, false);
    }
    if (playerTwoRoundWin) // if player two won the game
    {
        // create new player 1 object
        CPlayer* player1 = new CPlayer(sf::Keyboard::W, sf::Keyboard::S, sf::Keyboard::A, 
            sf::Keyboard::D, sf::Keyboard::V, { 800, 200 }, true);
    }
}


void WinScene::Update()
{
    mousePos = GetMousePos();

    std::cout << mousePos.x << "    " << mousePos.y << "\n";

    if (playerOneRoundWin || playerTwoRoundWin)
    {
        if (mousePos.x > 590 && mousePos.x < 690 && mousePos.y > 400 && mousePos.y < 500)
        {
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                NextRound();
            }
        }
    }
    
}


sf::Vector2f WinScene::GetMousePos()
{
    int x = sf::Mouse::getPosition(GetManager().GetWindow()).x;
    int y = sf::Mouse::getPosition(GetManager().GetWindow()).y;

    return sf::Vector2f(x, y);
}







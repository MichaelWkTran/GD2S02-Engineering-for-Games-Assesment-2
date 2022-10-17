// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
// (c) 2022 Media Design School
//
// File Name: WinScene.cpp
// Description: WinScene declaration file
// Authors: Sean David Palmer

#include "WinScene.h"
#include "CPlayer.h"
#include "CMenu.h"
#include "CMapSelector.h"
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

    // setup sf::Drawable (WIN SCENE)
    drawable = new sf::RectangleShape(sf::Vector2f(radius, radius));
    ((sf::RectangleShape*)drawable)->setFillColor(sf::Color().Black);
    transform.setPosition(640, 360);

    // restart button
    restart = new sf::RectangleShape(sf::Vector2f(100, 60));
    ((sf::RectangleShape*)restart)->setFillColor(sf::Color().White);
    restartTransform.setPosition(640, 280);
    restartTransform.setOrigin(50, 30);

    // home button
    home = new sf::RectangleShape(sf::Vector2f(100, 60));
    ((sf::RectangleShape*)home)->setFillColor(sf::Color().White);
    homeTransform.setPosition(640, 380);
    homeTransform.setOrigin(50, 30);

    // quit button
    quit = new sf::RectangleShape(sf::Vector2f(100, 60));
    ((sf::RectangleShape*)quit)->setFillColor(sf::Color().White);
    quitTransform.setPosition(640, 480);
    quitTransform.setOrigin(50, 30);



    winRoundString = "PLAYER WINS THE ROUND";
    winString = "PLAYER WINS";

    nextRoundString = "CONTINUE";

    scoreString[0] = "Player One Score: " + std::to_string(playerOneScore);
    scoreString[1] = "Player Two Score: " + std::to_string(playerTwoScore);

    homeString = "HOME";
    quitString = "QUIT";

    winText.setString(winRoundString); // win round

    // player wins text
    winText.setFillColor(sf::Color::Red);
    winText.setFont(GetManager().font);
    winText.setCharacterSize(20);
    winText.setPosition(transform.getPosition().x - 130, transform.getPosition().y - 220);

    // next round text
    nextRoundText.setString(nextRoundString);
    nextRoundText.setFillColor(sf::Color::Red);
    nextRoundText.setFont(GetManager().font);
    nextRoundText.setCharacterSize(18);
    nextRoundText.setPosition(restartTransform.getPosition().x - 45, restartTransform.getPosition().y - 10);

    // player one score display
    scoreText[0].setString(scoreString[0]);
    scoreText[0].setFillColor(sf::Color::Red);
    scoreText[0].setFont(GetManager().font);
    scoreText[0].setCharacterSize(20);
    scoreText[0].setPosition(10, 10);

    // player two score display
    scoreText[1].setString(scoreString[1]);
    scoreText[1].setFillColor(sf::Color::Red);
    scoreText[1].setFont(GetManager().font);
    scoreText[1].setCharacterSize(20);
    scoreText[1].setPosition(1000, 10);

    // home button
    homeText.setString(homeString);
    homeText.setFillColor(sf::Color::Red);
    homeText.setFont(GetManager().font);
    homeText.setCharacterSize(18);
    homeText.setPosition(homeTransform.getPosition().x - 25, homeTransform.getPosition().y - 10);

    // quit button
    quitText.setString(quitString);
    quitText.setFillColor(sf::Color::Red);
    quitText.setFont(GetManager().font);
    quitText.setCharacterSize(18);
    quitText.setPosition(quitTransform.getPosition().x - 25, quitTransform.getPosition().y - 10);
}


void WinScene::Draw()
{
    if (!visible) return;


    if (playerOneRoundWin || playerTwoRoundWin)
    {
        SetTransformValues(transform, drawable);
        SetTransformValues(restartTransform, restart);
        SetTransformValues(homeTransform, home);
        SetTransformValues(quitTransform, quit);

        // draw drawable and text
        GetManager().GetWindow().draw(winText);
        GetManager().GetWindow().draw(nextRoundText);
        GetManager().GetWindow().draw(homeText);
        GetManager().GetWindow().draw(quitText);
    }

    GetManager().GetWindow().draw(scoreText[0]);
    GetManager().GetWindow().draw(scoreText[1]);
    
}


void WinScene::NextRound()
{
    if (playerOneRoundWin || playerTwoRoundWin) // if player one won the game
    {
        // create new player 1 object
        CPlayer* player1 = new CPlayer(sf::Keyboard::W, sf::Keyboard::S, sf::Keyboard::A,
            sf::Keyboard::D, sf::Keyboard::V, { 800, 200 }, true);
        // create new player 2 object
        CPlayer* player2 = new CPlayer(sf::Keyboard::Up, sf::Keyboard::Down, sf::Keyboard::Left,
            sf::Keyboard::Right, sf::Keyboard::Slash, { 800, 500 }, false);
    }
}


void WinScene::Update()
{
    sf::Event event;

    mousePos = GetMousePos();

    scoreString[0] = "Player One Score: " + std::to_string(playerOneScore);
    scoreText[0].setString(scoreString[0]);

    scoreString[1] = "Player Two Score: " + std::to_string(playerTwoScore);
    scoreText[1].setString(scoreString[1]);

    // round/overall win text setup
    if (playerOneScore == 3 || playerTwoScore == 3)
    {
        winText.setString(winString); // win overall game
    }
    else { winText.setString(winRoundString); } // win round

    if (playerOneRoundWin || playerTwoRoundWin)
    {
        // next round/continue
        if (mousePos.x > 590 && mousePos.x < 690 && mousePos.y > 250 && mousePos.y < 310)
        {
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                std::cout << "NEXT ROUND";
                NextRound();
                // random level
            }
        }

        // home
        if (mousePos.x > 590 && mousePos.x < 690 && mousePos.y > 350 && mousePos.y < 410)
        {
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                std::cout << "home";
                CMenu::playGame = false;
                WinScene* winScene = new WinScene();
                // BUG - clicks controls when home button is pressed as its in the same place
            }
        }

        // quit
        if (mousePos.x > 590 && mousePos.x < 690 && mousePos.y > 450 && mousePos.y < 510)
        {
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                exit(0);
            }
        }


    }

}


void WinScene::SetTransformValues(sf::Transformable _transform, sf::Drawable* _drawable)
{
    // transform the drawable to m_Transfrom
    sf::Transformable* drawableTransform = dynamic_cast<sf::Transformable*>(_drawable);
    if (drawableTransform == nullptr)
    {
        std::cout << "ERROR: m_pDrawable in CGameObject must inherit from sf::Transformable\n";
        return;
    }

    // set values of transforms
    drawableTransform->setPosition(_transform.getPosition());
    drawableTransform->setScale(_transform.getScale());
    drawableTransform->setRotation(_transform.getRotation());
    drawableTransform->setOrigin(_transform.getOrigin());

    GetManager().GetWindow().draw(*_drawable);
}


sf::Vector2f WinScene::GetMousePos()
{
    int x = sf::Mouse::getPosition(GetManager().GetWindow()).x;
    int y = sf::Mouse::getPosition(GetManager().GetWindow()).y;

    return sf::Vector2f(x, y);
}







// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
// (c) 2022 Media Design School
//
// File Name: WinScene.cpp
// Description: WinScene declaration file
// Authors: Sean David Palmer

#include "CWinScene.h"
#include "CPlayer.h"
#include "CMenu.h"
#include "CMapSelector.h"
#include <iostream>


CWinScene::CWinScene()
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
    winText.setPosition(transform.getPosition().x - 155, transform.getPosition().y - 220);

    // next round text
    nextRoundText.setString(nextRoundString);
    nextRoundText.setFillColor(sf::Color::Red);
    nextRoundText.setFont(GetManager().font);
    nextRoundText.setCharacterSize(18);
    nextRoundText.setPosition(restartTransform.getPosition().x - 45, restartTransform.getPosition().y - 10);

    // player one score display
    scoreText[0].setString(scoreString[0]);
    scoreText[0].setFillColor(sf::Color::Blue);
    scoreText[0].setFont(GetManager().font);
    scoreText[0].setCharacterSize(18);
    scoreText[0].setPosition(5, 590);

    // player two score display
    scoreText[1].setString(scoreString[1]);
    scoreText[1].setFillColor(sf::Color::Red);
    scoreText[1].setFont(GetManager().font);
    scoreText[1].setCharacterSize(18);
    scoreText[1].setPosition(1110, 590);

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


void CWinScene::Draw()
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


void CWinScene::NextRound()
{
    if (playerOneRoundWin || playerTwoRoundWin) // if player one won the game
    {
        GetManager().ResetPlayers();
        GetManager().ResetWeaponTimer();
        GetManager().spawnWeapons = true;
    }
}


void CWinScene::Update()
{
    mousePos = GetMousePos();

    scoreString[0] = "Player One Score: " + std::to_string(playerOneScore);
    scoreText[0].setString(scoreString[0]);

    scoreString[1] = "Player Two Score: " + std::to_string(playerTwoScore);
    scoreText[1].setString(scoreString[1]);

    if (playerOneRoundWin)
    {
        winRoundString = "PLAYER ONE WINS THE ROUND";
    }
    if (playerTwoRoundWin)
    {
        winRoundString = "PLAYER TWO WINS THE ROUND";
    }

    winText.setString(winRoundString);// win round

    if (playerOneRoundWin || playerTwoRoundWin)
    {
        // next round/continue
        if (mousePos.x > 590 && mousePos.x < 690 && mousePos.y > 250 && mousePos.y < 310)
        {
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                std::cout << "NEXT ROUND";
                NextRound();
                int i = rand() % 4 + 1;
                GetManager().LoadNewLevel(std::to_string(i));
                GetManager().spawnWeapons = true;
            }
        }

        // home
        if (mousePos.x > 590 && mousePos.x < 690 && mousePos.y > 350 && mousePos.y < 410)
        {
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                std::cout << "home";
                CMenu::playGame = false;
                CWinScene* winScene = new CWinScene();
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


void CWinScene::SetTransformValues(sf::Transformable _transform, sf::Drawable* _drawable)
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


sf::Vector2f CWinScene::GetMousePos()
{
    return GetManager().GetWindow().mapPixelToCoords(sf::Mouse::getPosition(GetManager().GetWindow()));
}







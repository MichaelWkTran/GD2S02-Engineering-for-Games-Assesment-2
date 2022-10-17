// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
// (c) 2022 Media Design School
//
// File Name: CMenu.cpp
// Description: CMenu header file
// Authors: Sean David Palmer

#include "CMenu.h"
#include "WinScene.h"
#include <iostream>


CMenu::CMenu()
{
    playGame = false;
    controlsScreen = false;
    mapSelectScreen = false;

    buttonWidth = 100;
    buttonHeight = 50;

	mousePos = sf::Vector2f(0, 0);

    // setup CGameObject
    float radius = 500.0f;

    // set the origin of the SFML transform
    transform.setOrigin(radius / 2, radius / 2);

    // setup sf::Drawable     
    // (MENU BACKGROUND)
    drawable = new sf::RectangleShape(sf::Vector2f(radius, radius));
    ((sf::RectangleShape*)drawable)->setFillColor(sf::Color().Black);
    transform.setPosition(640, 360);

    // (MENU BANNER)
    bannerDrawable = new sf::RectangleShape(sf::Vector2f(300, 100));
    ((sf::RectangleShape*)bannerDrawable)->setFillColor(sf::Color().White);
    bannerTransform.setOrigin(150, 50);
    bannerTransform.setPosition(640, 180);

    // (PLAY BUTTON)
    playDrawable = new sf::RectangleShape(sf::Vector2f(buttonWidth, buttonHeight));
    ((sf::RectangleShape*)playDrawable)->setFillColor(sf::Color().White);
    playTransform.setOrigin(50, 25);
    playTransform.setPosition(640, 300);

    // (CONTROLS BUTTON)
    controlsDrawable = new sf::RectangleShape(sf::Vector2f(buttonWidth, buttonHeight));
    ((sf::RectangleShape*)controlsDrawable)->setFillColor(sf::Color().White);
    controlsTransform.setOrigin(50, 25);
    controlsTransform.setPosition(640, 400);

    // (QUIT BUTTON)
    quitDrawable = new sf::RectangleShape(sf::Vector2f(buttonWidth, buttonHeight));
    ((sf::RectangleShape*)quitDrawable)->setFillColor(sf::Color().White);
    quitTransform.setOrigin(50, 25);
    quitTransform.setPosition(640, 500);

     // (BACK BUTTON)
    backDrawable = new sf::RectangleShape(sf::Vector2f(buttonWidth, buttonHeight));
    ((sf::RectangleShape*)backDrawable)->setFillColor(sf::Color().White);
    backTransform.setOrigin(50, 25);
    backTransform.setPosition(480, 560);



    playString = "PLAY";
    controlsString = "CONTROLS";
    quitString = "QUIT";
    backString = "BACK";

    playText.setString(playString);
    playText.setFillColor(sf::Color::Red);
    playText.setFont(GetManager().font);
    playText.setCharacterSize(18);
    playText.setPosition(615, 290);

    controlsText.setString(controlsString);
    controlsText.setFillColor(sf::Color::Red);
    controlsText.setFont(GetManager().font);
    controlsText.setCharacterSize(18);
    controlsText.setPosition(590, 390);

    quitText.setString(quitString);
    quitText.setFillColor(sf::Color::Red);
    quitText.setFont(GetManager().font);
    quitText.setCharacterSize(18);
    quitText.setPosition(615, 490);

    backText.setString(backString);
    backText.setFillColor(sf::Color::Red);
    backText.setFont(GetManager().font);
    backText.setCharacterSize(18);
    backText.setPosition(455, 550);


}


void CMenu::Draw()
{
    if (!visible) return;

    if (!playGame)
    {
        SetTransformValues(transform, drawable);
        SetTransformValues(playTransform, playDrawable);
        SetTransformValues(controlsTransform, controlsDrawable);
        SetTransformValues(quitTransform, quitDrawable);
        SetTransformValues(bannerTransform, bannerDrawable);

        GetManager().GetWindow().draw(playText);
        GetManager().GetWindow().draw(controlsText);
        GetManager().GetWindow().draw(quitText);
    }

    if (controlsScreen)
    {
        SetTransformValues(transform, drawable);
        SetTransformValues(backTransform, backDrawable);
        GetManager().GetWindow().draw(backText);
        GetManager().GetWindow().draw(controlsText);
    }
}


void CMenu::Update()
{
    mousePos = WinScene::GetMousePos();

    if (!playGame) // at the main menu
    {
        // click play 
        if (mousePos.x > 590 && mousePos.x < 690 && mousePos.y > 275 && mousePos.y < 325)
        {
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                playGame = true;
                mapSelectScreen = true; // display map selector
            }
        }

        // click controls 
        if (mousePos.x > 590 && mousePos.x < 690 && mousePos.y > 375 && mousePos.y < 425)
        {
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                controlsScreen = true;
            }
        }

        // click quit
        if (mousePos.x > 590 && mousePos.x < 690 && mousePos.y > 475 && mousePos.y < 525)
        {
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                exit(0);
            }
        }
    }
    

    if (controlsScreen) // at the controls screen
    {
        controlsString = "                      LIST OF CONTROLS\n\n\nPlayer One:\n      WASD to Move\n"
            "      V to shoot"
            "\n\n\nPlayer Two:\n      Arrow Keys to Move\n"
            "      Forward Slash to shoot";
        controlsText.setString(controlsString);
        controlsText.setPosition(450, 190);

        if (mousePos.x > 430 && mousePos.x < 530 && mousePos.y > 535 && mousePos.y < 685)
        {
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                controlsScreen = false;
            }
        }

    }
    else
    {
        controlsString = "CONTROLS";
        controlsText.setString(controlsString);
        controlsText.setPosition(590, 390);
    }
}


void CMenu::SetTransformValues(sf::Transformable _transform, sf::Drawable* _drawable)
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


void CMenu::SetText(sf::Text _text, sf::String _string, float _xPos, float _yPos)
{
    /*_text.setString(_string);
    _text.setFillColor(sf::Color::Red);
    _text.setFont(GetManager().font);
    _text.setCharacterSize(25);
    _text.setPosition(_xPos, _yPos);*/
}


void CMenu::CreateDrawable(sf::Drawable* _drawable, sf::Transformable _transformable, int _xPos, int _yPos, int _xOrigin, int _yOrigin, int _width, int _height)
{
    /*_drawable = new sf::RectangleShape(sf::Vector2f(_width, _height));
    ((sf::RectangleShape*)_drawable)->setFillColor(sf::Color().White);
    _transformable.setOrigin(_xOrigin, _yOrigin);
    _transformable.setPosition(_xPos, _yPos);*/
}







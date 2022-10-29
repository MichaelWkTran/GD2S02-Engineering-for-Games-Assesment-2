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
    settingsScreen = false;

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
    playDrawable = new sf::RectangleShape(sf::Vector2f((float)buttonWidth, (float)buttonHeight));
    ((sf::RectangleShape*)playDrawable)->setFillColor(sf::Color().White);
    playTransform.setOrigin(50, 25);
    playTransform.setPosition(640, 275);

    // (CONTROLS BUTTON)
    controlsDrawable = new sf::RectangleShape(sf::Vector2f((float)buttonWidth, (float)buttonHeight));
    ((sf::RectangleShape*)controlsDrawable)->setFillColor(sf::Color().White);
    controlsTransform.setOrigin(50, 25);
    controlsTransform.setPosition(640, 350);

    // (SETTINGS BUTTON)
    settingsDrawable = new sf::RectangleShape(sf::Vector2f((float)buttonWidth, (float)buttonHeight));
    ((sf::RectangleShape*)settingsDrawable)->setFillColor(sf::Color().White);
    settingsTransform.setOrigin(50, 25);
    settingsTransform.setPosition(640, 425);

    // (QUIT BUTTON)
    quitDrawable = new sf::RectangleShape(sf::Vector2f((float)buttonWidth, (float)buttonHeight));
    ((sf::RectangleShape*)quitDrawable)->setFillColor(sf::Color().White);
    quitTransform.setOrigin(50, 25);
    quitTransform.setPosition(640, 500);

    // (BACK BUTTON)
    backDrawable = new sf::RectangleShape(sf::Vector2f((float)buttonWidth, (float)buttonHeight));
    ((sf::RectangleShape*)backDrawable)->setFillColor(sf::Color().White);
    backTransform.setOrigin(50, 25);
    backTransform.setPosition(480, 560);

    // (windowSize1 BUTTON)
    windowSize1Drawable = new sf::RectangleShape(sf::Vector2f(100, 30));
    ((sf::RectangleShape*)windowSize1Drawable)->setFillColor(sf::Color().White);
    windowSize1Transform.setOrigin(50, 25);
    windowSize1Transform.setPosition(565, 450);
    // (windowSize2 BUTTON)
    windowSize2Drawable = new sf::RectangleShape(sf::Vector2f(100, 30));
    ((sf::RectangleShape*)windowSize2Drawable)->setFillColor(sf::Color().White);
    windowSize2Transform.setOrigin(50, 25);
    windowSize2Transform.setPosition(725, 450);
    // (volume0 BUTTON)
    volume0Drawable = new sf::RectangleShape(sf::Vector2f(75, 30));
    ((sf::RectangleShape*)volume0Drawable)->setFillColor(sf::Color().White);
    volume0Transform.setOrigin(50, 25);
    volume0Transform.setPosition(495, 350);
    // (volume25 BUTTON)
    volume25Drawable = new sf::RectangleShape(sf::Vector2f(75, 30));
    ((sf::RectangleShape*)volume25Drawable)->setFillColor(sf::Color().White);
    volume25Transform.setOrigin(50, 25);
    volume25Transform.setPosition(575, 350);
    // (volume50 BUTTON)
    volume50Drawable = new sf::RectangleShape(sf::Vector2f(75, 30));
    ((sf::RectangleShape*)volume50Drawable)->setFillColor(sf::Color().White);
    volume50Transform.setOrigin(50, 25);
    volume50Transform.setPosition(655, 350);
    // (volume75 BUTTON)
    volume75Drawable = new sf::RectangleShape(sf::Vector2f(75, 30));
    ((sf::RectangleShape*)volume75Drawable)->setFillColor(sf::Color().White);
    volume75Transform.setOrigin(50, 25);
    volume75Transform.setPosition(735, 350);
    // (volume100 BUTTON)
    volume100Drawable = new sf::RectangleShape(sf::Vector2f(75, 30));
    ((sf::RectangleShape*)volume100Drawable)->setFillColor(sf::Color().White);
    volume100Transform.setOrigin(50, 25);
    volume100Transform.setPosition(815, 350);



    playString = "PLAY";
    controlsString = "CONTROLS";
    settingsString = "SETTINGS";
    quitString = "QUIT";
    backString = "BACK";

    playText.setString(playString);
    playText.setFillColor(sf::Color::Red);
    playText.setFont(GetManager().font);
    playText.setCharacterSize(18);
    playText.setPosition(615, 265);

    controlsText.setString(controlsString);
    controlsText.setFillColor(sf::Color::Red);
    controlsText.setFont(GetManager().font);
    controlsText.setCharacterSize(18);
    controlsText.setPosition(590, 340);

    settingsText.setString(settingsString);
    settingsText.setFillColor(sf::Color::Red);
    settingsText.setFont(GetManager().font);
    settingsText.setCharacterSize(18);
    settingsText.setPosition(595, 415);

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
        SetTransformValues(settingsTransform, settingsDrawable);
        SetTransformValues(quitTransform, quitDrawable);
        SetTransformValues(bannerTransform, bannerDrawable);

        GetManager().GetWindow().draw(playText);
        GetManager().GetWindow().draw(controlsText);
        GetManager().GetWindow().draw(settingsText);
        GetManager().GetWindow().draw(quitText);
    }

    if (controlsScreen)
    {
        SetTransformValues(transform, drawable);
        SetTransformValues(backTransform, backDrawable);
        GetManager().GetWindow().draw(backText);
        GetManager().GetWindow().draw(controlsText);
    }
    if (settingsScreen)
    {
        SetTransformValues(transform, drawable);
        //SetTransformValues(windowSize1Transform, windowSize1Drawable);
        //SetTransformValues(windowSize2Transform, windowSize2Drawable);
        SetTransformValues(volume0Transform, volume0Drawable);
        SetTransformValues(volume25Transform, volume25Drawable);
        SetTransformValues(volume50Transform, volume50Drawable);
        SetTransformValues(volume75Transform, volume75Drawable);
        SetTransformValues(volume100Transform, volume25Drawable);
        SetTransformValues(backTransform, backDrawable);
        GetManager().GetWindow().draw(backText);
        GetManager().GetWindow().draw(settingsText);
    }
}


void CMenu::Update()
{
    mousePos = WinScene::GetMousePos();

    if (!playGame && !controlsScreen && !settingsScreen) // at the main menu
    {
        // click play 
        if (mousePos.x > 590 && mousePos.x < 690 && mousePos.y > 250 && mousePos.y < 300)
        {
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                playGame = true;
                mapSelectScreen = true; // display map selector
            }
        }

        // click controls 
        if (mousePos.x > 590 && mousePos.x < 690 && mousePos.y > 325 && mousePos.y < 375)
        {
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                controlsScreen = true;
            }
        }

        // click settings 
        if (mousePos.x > 590 && mousePos.x < 690 && mousePos.y > 400 && mousePos.y < 450)
        {
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                settingsScreen = true;
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
    else if (settingsScreen) // at the settings screen
    {
        settingsString = "                             SETTINGS:\n\n\n\n\n                                Volume:"
            "\n\n    0%          25%         50%         75%        100%"
            "\n\n\n                            ";//Window Size : \n\n               1280x720               1920x1080";
        settingsText.setString(settingsString);
        settingsText.setPosition(450, 190);

        //if (mousePos.x > 430 && mousePos.x < 530 && mousePos.y > 535 && mousePos.y < 685)//back button
        if (mousePos.x > backTransform.getPosition().x - 50 && mousePos.x < backTransform.getPosition().x + 50 && mousePos.y > backTransform.getPosition().y - 25 && mousePos.y < backTransform.getPosition().y + 25)// back button
        {
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                settingsScreen = false;
            }
        }
        //if (mousePos.x > 515 && mousePos.x < 615 && mousePos.y > 435 && mousePos.y < 465)//window1
        //{
        //    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        //    {
        //        GetManager().GetWindow().setSize(sf::Vector2u(1280, 720));
        //        
        //        
        //    }
        //}
        //if (mousePos.x > 675 && mousePos.x < 775 && mousePos.y > 435 && mousePos.y < 465)//window 2
        //{
        //    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        //    {
        //        GetManager().GetWindow().setSize(sf::Vector2u(1920, 1080));


        //    }
        //}
        if (mousePos.x > 457.5f && mousePos.x < 532.5f && mousePos.y > 335.f && mousePos.y < 365.f)//vol 0
        {
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                GetManager().SetVolume(0.f);
                std::cout << "Vol Changed to 0\n";
                new CSound("gun7.wav");
            }
        }
        if (mousePos.x > 537.5f && mousePos.x < 612.5f && mousePos.y > 335.f && mousePos.y < 365.f)//vol 25
        {
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                GetManager().SetVolume(25.0f);
                std::cout << "Vol Changed to 25\n";
                new CSound("gun7.wav");
            }
        }
        if (mousePos.x > 617.5f && mousePos.x < 692.5f && mousePos.y > 335.f && mousePos.y < 365.f)//vol50
        {
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                GetManager().SetVolume(50.0f);
                std::cout << "Vol Changed to 50\n";
                new CSound("gun7.wav");
            }
        }
        if (mousePos.x > 697.5f && mousePos.x < 772.5f && mousePos.y > 335.f && mousePos.y < 365.f)//vol75
        {
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                GetManager().SetVolume(75.0f);
                std::cout << "Vol Changed to 75\n";
                new CSound("gun7.wav");
            }
        }
        if (mousePos.x > 777.5f && mousePos.x < 852.5 && mousePos.y > 335.f && mousePos.y < 365.f)//vol100
        {
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                GetManager().SetVolume(100.0f);
                std::cout << "Vol Changed to 100\n";
                new CSound("gun7.wav");
            }
        }

    }
    else
    {
        controlsString = "CONTROLS";
        controlsText.setString(controlsString);
        controlsText.setPosition(590, 340);

        settingsString = "SETTINGS";
        settingsText.setString(settingsString);
        settingsText.setPosition(595, 415);
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

void CMenu::SetVolume(float _volume)
{
    volumeLevel = _volume;
}







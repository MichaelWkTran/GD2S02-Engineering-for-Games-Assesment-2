#include "CMapSelector.h"
#include "CMenu.h"
#include "WinScene.h"
#include <iostream>


CMapSelector::CMapSelector()
{
    buttonWidth = 100;
    buttonHeight = 100;

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

    // (MAP 1 BUTTON)
    buttonDrawable[0] = new sf::RectangleShape(sf::Vector2f(buttonWidth, buttonHeight));
    ((sf::RectangleShape*)buttonDrawable[0])->setFillColor(sf::Color().White);
    buttonTransform[0].setOrigin(buttonWidth/2, buttonHeight/2);
    buttonTransform[0].setPosition(540, 280);

    // (MAP 2 BUTTON)
    buttonDrawable[1] = new sf::RectangleShape(sf::Vector2f(buttonWidth, buttonHeight));
    ((sf::RectangleShape*)buttonDrawable[1])->setFillColor(sf::Color().White);
    buttonTransform[1].setOrigin(buttonWidth/2, buttonHeight/2);
    buttonTransform[1].setPosition(740, 280);

    // (MAP 3 BUTTON)
    buttonDrawable[2] = new sf::RectangleShape(sf::Vector2f(buttonWidth, buttonHeight));
    ((sf::RectangleShape*)buttonDrawable[2])->setFillColor(sf::Color().White);
    buttonTransform[2].setOrigin(buttonWidth/2, buttonHeight/2);
    buttonTransform[2].setPosition(540, 430);

    //// (MAP 4 BUTTON)
    buttonDrawable[3] = new sf::RectangleShape(sf::Vector2f(buttonWidth, buttonHeight));
    ((sf::RectangleShape*)buttonDrawable[3])->setFillColor(sf::Color().White);
    buttonTransform[3].setOrigin(buttonWidth/2, buttonHeight/2);
    buttonTransform[3].setPosition(740, 430);

    //// (BACK BUTTON)
    backDrawable = new sf::RectangleShape(sf::Vector2f(100, 50));
    ((sf::RectangleShape*)backDrawable)->setFillColor(sf::Color().White);
    backTransform.setOrigin(100/2, 50/2);
    backTransform.setPosition(480, 560);

    //// (RANDOM BUTTON)
    randDrawable = new sf::RectangleShape(sf::Vector2f(100, 50));
    ((sf::RectangleShape*)randDrawable)->setFillColor(sf::Color().White);
    randTransform.setOrigin(100/2, 50/2);
    randTransform.setPosition(800, 560);




    headerString = "SELECT A LEVEL"; // assign header text values
    backString = "BACK";
    randString = "RANDOM";

    headerText.setString(headerString);
    headerText.setFillColor(sf::Color::Red);
    headerText.setFont(GetManager().font);
    headerText.setCharacterSize(30);
    headerText.setPosition(525, 150);

    for (int i = 0; i < 4; i++) // assign button text values
    {
        buttonString[i] = "LEVEL " + std::to_string(i + 1);
        buttonText[i].setString(buttonString[i]);
        buttonText[i].setFillColor(sf::Color::Red);
        buttonText[i].setFont(GetManager().font);
        buttonText[i].setCharacterSize(18);
    }

    buttonText[0].setPosition(505, 270);
    buttonText[1].setPosition(705, 270);
    buttonText[2].setPosition(505, 420);
    buttonText[3].setPosition(705, 420);

    backText.setString(backString);
    backText.setFillColor(sf::Color::Red);
    backText.setFont(GetManager().font);
    backText.setCharacterSize(18);
    backText.setPosition(455, 550);

    randText.setString(randString);
    randText.setFillColor(sf::Color::Red);
    randText.setFont(GetManager().font);
    randText.setCharacterSize(18);
    randText.setPosition(760, 550);
}


void CMapSelector::Draw()
{
    if (!visible) return;

    if (CMenu::mapSelectScreen)
    {
        SetTransformValues(transform, drawable);
        SetTransformValues(backTransform, backDrawable);
        SetTransformValues(randTransform, randDrawable);

        // draw buttons
        for (int i = 0; i < 4; i++)
        {
            SetTransformValues(buttonTransform[i], buttonDrawable[i]);
            GetManager().GetWindow().draw(buttonText[i]);
        }
        
        GetManager().GetWindow().draw(headerText);
        GetManager().GetWindow().draw(backText);
        GetManager().GetWindow().draw(randText);
    }   
}


void CMapSelector::Update()
{
    mousePos = WinScene::GetMousePos();
    
    if (CMenu::mapSelectScreen)
    {
        // level one selected
        if (mousePos.x > 490 && mousePos.x < 590 && mousePos.y > 255 && mousePos.y < 305)
        {
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                LoadLevel1();
                CMenu::mapSelectScreen = false;
            }
        }

        // level two selected
        if (mousePos.x > 690 && mousePos.x < 790 && mousePos.y > 255 && mousePos.y < 305)
        {
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                LoadLevel2();
                CMenu::mapSelectScreen = false;
            }
        }

        // level three selected
        if (mousePos.x > 490 && mousePos.x < 590 && mousePos.y > 405 && mousePos.y < 455)
        {
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                LoadLevel3();
                CMenu::mapSelectScreen = false;
            }
        }

        // level four selected
        if (mousePos.x > 690 && mousePos.x < 790 && mousePos.y > 405 && mousePos.y < 455)
        {
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                LoadLevel4();
                CMenu::mapSelectScreen = false;
            }
        }


        // back button
        if (mousePos.x > 430 && mousePos.x < 530 && mousePos.y > 535 && mousePos.y < 585)
        {
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                CMenu::mapSelectScreen = false; // hide map select screen
                CMenu::playGame = false; // display main menu
            }
        }

         // random button
        if (mousePos.x > 750 && mousePos.x < 850 && mousePos.y > 535 && mousePos.y < 585)
        {
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                LoadRandomLevel();
                CMenu::mapSelectScreen = false; // hide map select screen
            }
        }
    }
}


void CMapSelector::SetTransformValues(sf::Transformable _transform, sf::Drawable* _drawable)
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


void CMapSelector::LoadLevel1()
{
}


void CMapSelector::LoadLevel2()
{
}


void CMapSelector::LoadLevel3()
{
}


void CMapSelector::LoadLevel4()
{
}


void CMapSelector::LoadRandomLevel()
{
}

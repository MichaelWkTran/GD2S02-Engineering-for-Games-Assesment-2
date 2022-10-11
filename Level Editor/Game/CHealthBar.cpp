// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
// (c) 2022 Media Design School
//
// File Name : CHealthBar.cpp
// Description: methods of CHealthBar class
// Authors: Lucas Manssen

#include "CHealthBar.h"

// Initialize parameters (size, position, color, player owner)
CHealthBar::CHealthBar(sf::Vector2f _barPosition, CPlayer* _player)
{
	// Initialize parameters
	playerObject = _player;

	maxPlayerHealth = playerObject->maxHealth;
	playerHealth = playerObject->health;

	barSize.x = 20.f;
	barSize.y = 15.f;


	// Initialize health bar rectangle shapes
	sf::Vector2f tempVector;
	tempVector.x = barSize.x * maxPlayerHealth;

	barBackground.setFillColor(sf::Color::Black);
	barBackground.setOutlineThickness(0.1f);
	barBackground.setOutlineColor(sf::Color::Black);
	barBackground.setPosition(_barPosition);
	barBackground.setSize(tempVector);

	barFill.setFillColor(sf::Color::Red);
	barFill.setOutlineThickness(1.f);
	barFill.setOutlineColor(sf::Color::Black);
	barFill.setPosition(_barPosition);
	barFill.setSize(tempVector);


}

CHealthBar::~CHealthBar()
{
}

// Update health bar size, and player health parameter. called once per frame
void CHealthBar::Update()
{
	if (playerObject != NULL)
	{
		// Update player HP
		playerHealth = playerObject->health;

		// Update barFill size according to current HP
		barFill.setSize(sf::Vector2f(barSize.x * playerHealth, barSize.y));
		barBackground.setSize(sf::Vector2f(200.0f, 15.0f));
	}
	if (playerObject == NULL)
	{
		// Update player HP
		playerHealth = 0;

		// Update barFill size
		barFill.setSize(sf::Vector2f(0.0f, barSize.y));
		barBackground.setSize(sf::Vector2f(200.0f, 15.0f));
	}

}

// Display updated health bar to frame. called once per frame
void CHealthBar::Draw()
{
	sf::Transformable* drawableTransform = dynamic_cast<sf::Transformable*>(&barFill);
	if (drawableTransform == nullptr)
	{
		std::cout << "ERROR: m_Drawable in CGameObject must inherit from sf::Transformable\n";
		return;
	}

	sf::Transformable* drawableTransform2 = dynamic_cast<sf::Transformable*>(&barBackground);
	if (drawableTransform2 == nullptr)
	{
		std::cout << "ERROR: m_Drawable in CGameObject must inherit from sf::Transformable\n";
		return;
	}

	/*drawableTransform->setPosition(transform.getPosition());
	drawableTransform->setScale(transform.getScale());
	drawableTransform->setRotation(transform.getRotation());
	drawableTransform->setOrigin(transform.getOrigin());*/

	// Draw both bars to frame
	GetManager().GetWindow().draw(barBackground);
	GetManager().GetWindow().draw(barFill);


}

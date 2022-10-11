// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
// (c) 2022 Media Design School
//
// File Name : CWeaponUI.cpp
// Description: methods of CWeaponUI class
// Authors: Lucas Manssen
#include "CWeaponUI.h"

// constructor
CWeaponUI::CWeaponUI(sf::Vector2f _elementPos, sf::Vector2f _iconPos, sf::Vector2f _textPos, CPlayer* _player)
{
	// set up player object
	playerObject = _player;

	// set up rectangle shapes, textures, and string
	uiIconRect.setFillColor(sf::Color::White);
	uiIconRect.setSize(sf::Vector2f(120.f, 30.f));
	uiIconRect.setPosition(_iconPos);
	uiIconRect.setOutlineThickness(0.f);
	uiIconRect.setOutlineColor(sf::Color::Black);

	uiBoxRect.setFillColor(sf::Color(102, 106, 112));
	uiBoxRect.setSize(sf::Vector2f(155.f, 75.f));
	uiBoxRect.setPosition(_elementPos);
	uiBoxRect.setOutlineThickness(1.f);
	uiBoxRect.setOutlineColor(sf::Color::Black);

	uiIconTex.loadFromFile("Assets/Sprites/weaponSprites/sideOnPistol.png");
	uiIconRect.setTexture(&uiIconTex);

	uiString = "Pistol";

	uiText.setString(uiString);
	uiText.setFillColor(sf::Color::Black);
	uiText.setFont(GetManager().font);
	uiText.setCharacterSize(20);
	uiText.setPosition(_textPos);
}

CWeaponUI::~CWeaponUI()
{
}

// update textures
void CWeaponUI::Update()
{
	if (playerObject != NULL)
	{
		// check for updates to currently held weapon, and update appropriately
		if (playerObject->heldWeaponInt == 0)
		{
			// pistol
			uiIconTex.loadFromFile("Assets/Sprites/weaponSprites/sideOnPistol.png");
			uiIconRect.setTexture(&uiIconTex);
			uiString = "Pistol";
			uiText.setString(uiString);
			
		}
		if (playerObject->heldWeaponInt == 1)
		{
			// rifle
			uiIconTex.loadFromFile("Assets/Sprites/weaponSprites/sideOnRifle.png");
			uiIconRect.setTexture(&uiIconTex);
			uiString = "Rifle";
			uiText.setString(uiString);
			
		}
		if (playerObject->heldWeaponInt == 2)
		{
			// sniper
			uiIconTex.loadFromFile("Assets/Sprites/weaponSprites/sideOnSniper.png");
			uiIconRect.setTexture(&uiIconTex);
			uiString = "Sniper";
			uiText.setString(uiString);
		}
		if (playerObject->heldWeaponInt == 3)
		{
			// shotgun
			uiIconTex.loadFromFile("Assets/Sprites/weaponSprites/sideOnShotgun.png");
			uiIconRect.setTexture(&uiIconTex);
			uiString = "Shotgun";
			uiText.setString(uiString);
		}
	}
}

// draw to frame
void CWeaponUI::Draw()
{
	sf::Transformable* drawableTransform = dynamic_cast<sf::Transformable*>(&uiIconRect);
	if (drawableTransform == nullptr)
	{
		std::cout << "ERROR: m_Drawable in CGameObject must inherit from sf::Transformable\n";
		return;
	}
	sf::Transformable* drawableTransform2 = dynamic_cast<sf::Transformable*>(&uiBoxRect);
	if (drawableTransform == nullptr)
	{
		std::cout << "ERROR: m_Drawable in CGameObject must inherit from sf::Transformable\n";
		return;
	}
	// Draw both bars to frame
	GetManager().GetWindow().draw(uiBoxRect);
	GetManager().GetWindow().draw(uiIconRect);
	GetManager().GetWindow().draw(uiText);
}

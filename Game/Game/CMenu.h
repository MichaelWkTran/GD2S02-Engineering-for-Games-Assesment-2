// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
// (c) 2022 Media Design School
//
// File Name: CMenu.h
// Description: CMenu header file
// Authors: Sean David Palmer

#pragma once
#include "CManager.h"
#include "CSound.h"
#include <SFML/Graphics.hpp>

class CMenu : public CGameObject
{
public:
	static bool playGame;
	static bool controlsScreen;
	static bool mapSelectScreen;
	bool mouseHeld;
	static bool settingsScreen;

	// transform variables
	sf::Transformable bannerTransform; // menu banner
	sf::Transformable playTransform; // play button
	sf::Transformable controlsTransform; // controls button
	sf::Transformable settingsTransform; // settings button
	sf::Transformable quitTransform; // quit button
	sf::Transformable backTransform; // back button in controls & settings

	sf::Transformable windowSize1Transform; // settings option button transform in settings
	sf::Transformable windowSize2Transform; // settings option button transform in settings
	sf::Transformable volume0Transform; // settings option button transform in settings
	sf::Transformable volume25Transform; // settings option button transform in settings
	sf::Transformable volume50Transform; // settings option button transform in settings
	sf::Transformable volume75Transform; // settings option button transform in settings
	sf::Transformable volume100Transform; // settings option button transform in settings

	sf::Vector2f mousePos;

	float volumeLevel;

	CMenu();

	void Draw();
	void Update();
	void SetTransformValues(sf::Transformable _transform, sf::Drawable* _drawable);
	void SetText(sf::Text _text, sf::String _string, float _xPos, float _yPos);
	void CreateDrawable(sf::Drawable* _drawable, sf::Transformable _transformable,
		int _xPos, int _yPos, int _xOrigin, int _yOrigin, int _width, int _height);
	void SetVolume(float _volume);

private:
	int buttonHeight;
	int buttonWidth;

	sf::Drawable* bannerDrawable;
	sf::Drawable* playDrawable;
	sf::Drawable* controlsDrawable;
	sf::Drawable* settingsDrawable;
	sf::Drawable* quitDrawable;
	sf::Drawable* backDrawable;
	sf::Drawable* windowSize1Drawable;
	sf::Drawable* windowSize2Drawable;
	sf::Drawable* volume0Drawable;
	sf::Drawable* volume25Drawable;
	sf::Drawable* volume50Drawable;
	sf::Drawable* volume75Drawable;
	sf::Drawable* volume100Drawable;

	sf::Text playText;
	sf::Text controlsText;
	sf::Text settingsText;
	sf::Text quitText;
	sf::Text backText;
	sf::Text titleText;

	sf::String playString;
	sf::String controlsString;
	sf::String settingsString;
	sf::String quitString;
	sf::String backString;
	sf::String titleString;


};


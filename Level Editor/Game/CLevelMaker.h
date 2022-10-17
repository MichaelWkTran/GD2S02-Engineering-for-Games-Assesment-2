#pragma once
#include "CMapPlaceBase.h"
#include "GlobalEnumInclude.h"

class CLevelMaker
{
private:
	int selectedPlacement = 0;
	int arenaSizeX = 30;
	int arenaSizeY = 17;
	int rotationValue = 0;
	CMapPlaceBase*** arena = nullptr;
	sf::Vector2f playerSpawns[2];

	void CheckPlace(sf::Vector2f _mousePos);
public:
	void Render();
	CLevelMaker();

	void Update();
	void SaveLevel();
	void LoadLevel();
};


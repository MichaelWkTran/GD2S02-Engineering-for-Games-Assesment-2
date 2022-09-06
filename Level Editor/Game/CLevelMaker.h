#pragma once
#include "CWall.h"
#include "GlobalEnumInclude.h"

class CLevelMaker
{
private:
	int selectedPlacement = 0;
	int arenaSizeX = 40;
	int arenaSizeY = 20;
	int rotationValue = 0;
	CMapPlaceBase*** arena = nullptr;

	void CheckPlace(sf::Vector2f _mousePos);
public:
	void Render();
	CLevelMaker();

	void Update();
	void SaveLevel();
	void LoadLevel();
};


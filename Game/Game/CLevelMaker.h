#pragma once
#include "CWall.h"
#include "GlobalEnumInclude.h"

class CLevelMaker
{
private:
	int selectedPlacement = 0;
	int arenaSizeX = 30;
	int arenaSizeY = 30;
	CMapPlaceBase*** arena = nullptr;

	void CheckPlace(sf::Vector2f _mousePos);
public:
	void Render();
	CLevelMaker();

	void Update();
	void SaveLevel();
	void LoadLevel();
};


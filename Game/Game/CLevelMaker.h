#pragma once
#include "CWall.h"
#include "GlobalEnumInclude.h"

class CLevelMaker
{
private:
	int selectedPlacement = 0;
	int arenaSizeX = 0;
	int arenaSizeY = 0;
	CMapPlaceBase*** arena = nullptr;
	
	void LoadLevel();
public:
	sf::Vector2f playerSpawns[2];
	void Render();
	CLevelMaker();

	void Update();
	void LoadLevel(std::string _path);
};


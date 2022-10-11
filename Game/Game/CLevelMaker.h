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
	void Render();
	CLevelMaker();

	void Update();
	void LoadLevel(std::string _path);
};


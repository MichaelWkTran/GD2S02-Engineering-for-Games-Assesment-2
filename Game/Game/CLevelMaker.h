#pragma once
#include "CWall.h"
#include "GlobalEnumInclude.h"
#include <vector>

class CWeaponBox;

class CLevelMaker
{
private:
	int selectedPlacement = 0;
	int arenaSizeX = 0;
	int arenaSizeY = 0;
	CMapPlaceBase*** arena = nullptr;
	
	void LoadLevel();
public:
	bool shouldDelete = false;
	sf::Vector2f playerSpawns[2];
	void Render();
	void SpawnWeaponBox();

	void CleanUp();
	void ReplaceWithGround(CWall* _block);

	void LoadLevel(std::string _path);
};


#pragma once
#include "CWall.h"
#include "GlobalEnumInclude.h"

class CLevelMaker
{
private:
	struct Button
	{
		int objectToSpawn = 0;
	};

	int arenaSize = 30;
	CGameObject* arena[30][30];

	
public:
	void Render();
	CLevelMaker();
	void SaveLevel();
	void LoadLevel();
};


#include "CLevelMaker.h"
#include "CGround.h"
#include "CManager.h"
#include "CSpikeTrap.h"
#include "CTurret.h"
#include "CWeaponBox.h"
#include <Shobjidl.h.>
#include <Shlwapi.h>
#include <atlbase.h>
#include <fstream>
#include <iostream>
#include <string>

void CLevelMaker::Render()
{
	for (int i = 0; i < arenaSizeX; i++)
	{
		for (int j = 0; j < arenaSizeY; j++)
		{
			arena[i][j]->Draw();
		}
	}
}

void CLevelMaker::SpawnWeaponBox()
{
	int x = rand() % arenaSizeX;
	int y = rand() % arenaSizeY;
	bool run = true;
	while (!dynamic_cast<CGround*>(arena[x][y]))
	{
		x = rand() % arenaSizeX;
		y = rand() % arenaSizeY;
	}

	sf::Vector2f spawnPos = arena[x][y]->transform.getPosition();

	GetManager().weaponBoxes.push_back(new CWeaponBox(spawnPos));
	if (GetManager().weaponBoxes.size() > GetManager().maxBoxes)
	{
		GetManager().weaponBoxes[0]->DeleteObject();
		GetManager().weaponBoxes.erase(GetManager().weaponBoxes.begin());
	}
}

void CLevelMaker::CleanUp()
{
	for (int i = 0; i < arenaSizeX; i++)
	{
		for (int j = 0; j < arenaSizeY; j++)
		{
			if (arena[i][j] != nullptr)
			{
				arena[i][j]->DeleteObject();
				arena[i][j] = nullptr;
			}
		}
	}

	for (CWeaponBox* weaponBox : GetManager().weaponBoxes) weaponBox->DeleteObject();
	GetManager().weaponBoxes.clear();
}

void CLevelMaker::ReplaceWithGround(CWall* _block)
{
	for (int i = 0; i < arenaSizeX; i++)
	{
		for (int j = 0; j < arenaSizeY; j++)
		{
			if (arena[i][j] == _block)
			{
				arena[i][j] = new CGround(sf::Vector2f((32.0f * i) + 200.0f, (32.0f * j) + 100.0f), 0.0f);
				GetManager().PlaceObjectAtFront(arena[i][j]);
				i = arenaSizeX;
				j = arenaSizeY;
			}
		}
	}
}

void CLevelMaker::LoadLevel()
{
	IFileOpenDialog* fileOpen;
	HRESULT hr = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_ALL, IID_IFileOpenDialog, reinterpret_cast<void**>(&fileOpen));

	if (SUCCEEDED(hr))
	{
		// Show the Open dialog box.
		hr = fileOpen->Show(NULL);

		// Get the file name from the dialog box.
		if (SUCCEEDED(hr))
		{
			IShellItem* item;
			hr = fileOpen->GetResult(&item);
			if (SUCCEEDED(hr))
			{
				PWSTR pszFilePath;
				hr = item->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath);

				// Display the file name to the user.
				if (SUCCEEDED(hr))
				{
					USES_CONVERSION;

					std::string temp;

					temp = PathFindExtensionA(W2A(pszFilePath));

					if (temp == ".txt")
					{
						LoadLevel(W2A(pszFilePath));
					}
					CoTaskMemFree(pszFilePath);
				}
				item->Release();
			}
		}
		fileOpen->Release();
	}
}

void CLevelMaker::LoadLevel(std::string _path)
{
	CleanUp();

	// set up the variables and open the file
	std::fstream saveFile;
	std::string Path = _path;
	saveFile.open(Path, std::ios::in | std::ios::trunc);

	std::ifstream inFile;
	inFile.open(Path.c_str());

	int objType;
	int k;
	int l;
	float rotation;

	for (int i = 0; i < arenaSizeY; i++)
	{
		delete arena[i];
		arena[i] = nullptr;
	}

	delete arena;

	inFile >> arenaSizeX;
	inFile >> arenaSizeY;

	arena = new CMapPlaceBase * *[arenaSizeX];

	for (int i = 0; i < arenaSizeX; i++)
	{
		arena[i] = new CMapPlaceBase * [arenaSizeY];
	}

	for (int i = 0; i < arenaSizeX; i++)
	{
		for (int j = 0; j < arenaSizeY; j++)
		{
			arena[i][j] = nullptr;
		}
	}

	// get player spawn positions
	inFile >> playerSpawns[0].x;
	inFile >> playerSpawns[0].y;
	inFile >> playerSpawns[1].x;
	inFile >> playerSpawns[1].y;

	while (inFile)
	{
		// read name, x, y, and rotation
		inFile >> objType;
		inFile >> k;
		inFile >> l;
		inFile >> rotation;

		float xOffset = 160.0f;
		float yOffset = 50.0f;

		// decide which object to place
		switch (objType)
		{
		case Ground:
			arena[k][l] = new CGround(sf::Vector2f((32.0f * k) + xOffset, (32.0f * l) + yOffset), rotation);
			break;
		case UnbreakableWall:
			arena[k][l] = new CWall(sf::Vector2f((32.0f * k) + xOffset, (32.0f * l) + yOffset), rotation);
			break;
		case BreakableWall:
			arena[k][l] = new CWall(sf::Vector2f((32.0f * k) + xOffset, (32.0f * l) + yOffset), rotation, true);
			break;
		case SpikeTrap:
			arena[k][l] = new CSpikeTrap(sf::Vector2f((32.0f * k) + xOffset, (32.0f * l) + yOffset));
			break;
		case Turret:
			arena[k][l] = new CTurret(sf::Vector2f((32.0f * k) + xOffset, (32.0f * l) + yOffset));
			break;
		}
	}
	saveFile.close();

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < arenaSizeX; j++)
		{
			for (int p = 0; p < arenaSizeY; p++)
			{
				if (i == 0)
				{
					if (dynamic_cast<CTurret*>(arena[j][p]))
					{
						GetManager().PlaceObjectAtFront(arena[j][p]);
					}
				}
				else
				{
					if (!dynamic_cast<CTurret*>(arena[j][p]))
					{
						GetManager().PlaceObjectAtFront(arena[j][p]);
					}
				}
			}
		}
	}
}

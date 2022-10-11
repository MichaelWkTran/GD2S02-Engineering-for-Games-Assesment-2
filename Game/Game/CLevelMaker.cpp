#include "CLevelMaker.h"
#include "CGround.h"
#include "CManager.h"
#include "CSpikeTrap.h"
#include "CTurret.h"
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

CLevelMaker::CLevelMaker()
{
	
}

void CLevelMaker::Update()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && sf::Keyboard::isKeyPressed(sf::Keyboard::L))
	{
		LoadLevel();
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

		// decide which object to place
		switch (objType)
		{
		case Ground:
			arena[k][l] = new CGround(sf::Vector2f(32 * k + 200, 32 * l + 100), rotation);
			break;
		case UnbreakableWall:
			arena[k][l] = new CWall(sf::Vector2f(32 * k + 200, 32 * l + 100), rotation);
			break;
		case BreakableWall:
			arena[k][l] = new CWall(sf::Vector2f(32 * k + 200, 32 * l + 100), rotation, true);
			break;
		case SpikeTrap:
			arena[k][l] = new CSpikeTrap(sf::Vector2f(32 * k + 200, 32 * l + 100));
			break;
		case Turret:
			arena[k][l] = new CTurret(sf::Vector2f(32 * k + 200, 32 * l + 100));
			break;
		}
	}
	saveFile.close();
}

#include "CLevelMaker.h"
#include "CGround.h"
#include "CManager.h"
#include "CSpikeTrap.h"
#include "CTurret.h"
#include "CWall.h"
#include <Shobjidl.h.>
#include <Shlwapi.h>
#include <atlbase.h>
#include <fstream>
#include <iostream>
#include <string>

/// <summary>
/// renders all the map objects
/// </summary>
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

/// <summary>
/// makes an arena based on the X and Y from the header, fills it with a temp map of a rectangle / square
/// </summary>
CLevelMaker::CLevelMaker()
{
	// initialize player spawn locations
	playerSpawns[0] = { 0, 0 };
	playerSpawns[1] = { 10, 10 };

	// make an array of pointers to arrays
	arena = new CMapPlaceBase**[arenaSizeX];

	// make arrays that the previous pointers are pointing to
	for (int i = 0; i < arenaSizeX; i++)
	{
		arena[i] = new CMapPlaceBase*[arenaSizeY];
	}

	// fill the array and make the temp map
	for (int i = 0; i < arenaSizeX; i++)
	{
		for (int j = 0; j < arenaSizeY; j++)
		{
			if (i == 0 || i == arenaSizeX - 1 || j == 0 || j == arenaSizeY - 1)
			{
				arena[i][j] = new CWall(sf::Vector2f(32 * i + 200, 32 * j + 100), 0);
			}
			else
			{
				arena[i][j] = new CGround(sf::Vector2f(32 * i + 200, 32 * j + 100), 0);
			}
		}
	}
}

/// <summary>
/// checks the spot the user is trying to place an object
/// </summary>
/// <param name="_mousePos"></param>
void CLevelMaker::CheckPlace(sf::Vector2f _mousePos)
{
	// loop through all map objects
	for (int i = 0; i < arenaSizeX; i++)
	{
		for (int j = 0; j < arenaSizeY; j++)
		{
			// check the spot they are trying to replace, and that its not the same object
			if (((sf::RectangleShape*)arena[i][j]->GetDrawable())->getGlobalBounds().contains(_mousePos) && arena[i][j]->objType != selectedPlacement)
			{
				// decide what to place
				switch (selectedPlacement)
				{
				case Ground:
					arena[i][j]->DeleteObject();
					arena[i][j] = new CGround(sf::Vector2f(32 * i + 200, 32 * j + 100), rotationValue);
					break;
				case UnbreakableWall:
					arena[i][j]->DeleteObject();
					arena[i][j] = new CWall(sf::Vector2f(32 * i + 200, 32 * j + 100), rotationValue, false);
					break;
				case BreakableWall:
					arena[i][j]->DeleteObject();
					arena[i][j] = new CWall(sf::Vector2f(32 * i + 200, 32 * j + 100), rotationValue, true);
					break;
				case SpikeTrap:
					arena[i][j]->DeleteObject();
					arena[i][j] = new CSpikeTrap(sf::Vector2f(32 * i + 200, 32 * j + 100));
					break;
				case Turret:
					arena[i][j]->DeleteObject();
					arena[i][j] = new CTurret(sf::Vector2f(32 * i + 200, 32 * j + 100));
					break;
				}
				// get out of the for loops
				i = arenaSizeX;
				j = arenaSizeY;
			}
		}
	}
}

/// <summary>
/// check input
/// </summary>
void CLevelMaker::Update()
{
	// check if the user is trying to place a tile
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		CheckPlace(GetManager().GetWindow().mapPixelToCoords(sf::Mouse::getPosition(GetManager().GetWindow())));
	}

	// sawp the object currently being place to the one the user switched to
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
		{
			playerSpawns[0] = GetManager().GetWindow().mapPixelToCoords(sf::Mouse::getPosition(GetManager().GetWindow()));
		}
		else
		{
			selectedPlacement = Ground;
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
		{
			playerSpawns[1] = GetManager().GetWindow().mapPixelToCoords(sf::Mouse::getPosition(GetManager().GetWindow()));
		}
		else
		{
			selectedPlacement = UnbreakableWall;
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
	{
		selectedPlacement = BreakableWall;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))
	{
		selectedPlacement = SpikeTrap;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5))
	{
		selectedPlacement = Turret;
	}

	// rotate left and right
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
	{
		rotationValue -= 90;
		if (rotationValue == -90)
			rotationValue = 0;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
	{
		rotationValue += 90;
		if (rotationValue == 360)
			rotationValue = 0;
	}

	// ctrl + s and ctrl + l to save and load levels
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		SaveLevel();
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && sf::Keyboard::isKeyPressed(sf::Keyboard::L))
	{
		LoadLevel();
	}
}

/// <summary>
/// saves the current map layout to a txt file
/// </summary>
void CLevelMaker::SaveLevel()
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
						// open the file
						std::fstream saveFile;
						std::string path = W2A(pszFilePath);
						saveFile.open(path, std::ios::out | std::ios::trunc);

						// save the arena size
						saveFile << arenaSizeX << "\n" << arenaSizeY << "\n";

						// save player spawn positions
						saveFile << playerSpawns[0].x << "\n" << playerSpawns[0].y << "\n";
						saveFile << playerSpawns[1].x << "\n" << playerSpawns[1].y << "\n";

						//save each spot in the arena
						for (int i = 0; i < arenaSizeX; i++)
						{
							for (int j = 0; j < arenaSizeY; j++)
							{
								saveFile << arena[i][j]->objType << "\n" << i << "\n" << j << "\n" << ((sf::Shape*)arena[i][j]->GetDrawable())->getRotation() << "\n";
							}
						}

						saveFile.close();
					}
					CoTaskMemFree(pszFilePath);
				}
				item->Release();
			}
		}
		fileOpen->Release();
	}
}

/// <summary>
/// load a layout from a txt file
/// </summary>
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
						// clear the lists so no etra objects

						// set up the variables and open the file
						std::fstream saveFile;
						std::string Path = W2A(pszFilePath);
						saveFile.open(Path, std::ios::in | std::ios::trunc);

						std::ifstream inFile;
						inFile.open(Path.c_str());

						// variables to store info
						int objType;
						int k;
						int l;
						float rotation;

						// delete the current arena
						for (int i = 0; i < arenaSizeY; i++)
						{
							delete arena[i];
							arena[i] = nullptr;
						}

						delete arena;

						// get the new arena size
						inFile >> arenaSizeX;
						inFile >> arenaSizeY;

						// set up the arena
						arena = new CMapPlaceBase * *[arenaSizeX];

						for (int i = 0; i < arenaSizeX; i++)
						{
							arena[i] = new CMapPlaceBase * [arenaSizeY];
						}

						// initialize as nullptrs
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
								arena[k][l] = new CWall(sf::Vector2f(32 * k + 200, 32 * l + 100), rotationValue, true);
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
					CoTaskMemFree(pszFilePath);
				}
				item->Release();
			}
		}
		fileOpen->Release();
	}
}

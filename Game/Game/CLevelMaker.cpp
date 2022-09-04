#include "CLevelMaker.h"
#include "CGround.h"
#include "CManager.h"
#include <Shobjidl.h.>
#include <Shlwapi.h>
#include <atlbase.h>
#include <fstream>
#include <iostream>
#include <string>

void CLevelMaker::Render()
{
	for (int i = 0; i < arenaSize; i++)
	{
		for (int j = 0; j < arenaSize; j++)
		{
			arena[i][j]->Draw();
		}
	}
}

CLevelMaker::CLevelMaker()
{
	for (int i = 0; i < arenaSize; i++)
	{
		for (int j = 0; j < arenaSize; j++)
		{
			if (i == 0 || i == arenaSize - 1 || j == 0 || j == arenaSize - 1)
			{
				arena[i][j] = new CWall(sf::Vector2f(32 * i + 200, 32 * j));
			}
			else
			{
				arena[i][j] = new CGround(sf::Vector2f(32 * i + 200, 32 * j));
			}
		}
	}
}

void CLevelMaker::CheckPlace(sf::Vector2f _mousePos)
{
	for (int i = 0; i < arenaSize; i++)
	{
		for (int j = 0; j < arenaSize; j++)
		{
			if (((sf::RectangleShape*)arena[i][j]->GetDrawable())->getGlobalBounds().contains(_mousePos))
			{
				switch (selectedPlacement)
				{
				case Ground:
					arena[i][j]->DeleteObject();
					arena[i][j] = new CGround(sf::Vector2f(32 * i + 200, 32 * j));
					break;
				case UnbreakableWall:
					arena[i][j]->DeleteObject();
					arena[i][j] = new CWall(sf::Vector2f(32 * i + 200, 32 * j));
					break;
				case BreakableWall:
					break;
				}
				i = arenaSize;
				j = arenaSize;
			}
		}
	}
}

void CLevelMaker::Update()
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		CheckPlace(GetManager().GetWindow().mapPixelToCoords(sf::Mouse::getPosition(GetManager().GetWindow())));
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
	{
		selectedPlacement = Ground;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
	{
		selectedPlacement = UnbreakableWall;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		SaveLevel();
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && sf::Keyboard::isKeyPressed(sf::Keyboard::L))
	{
		LoadLevel();
	}
}

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

						for (int i = 0; i < arenaSize; i++)
						{
							for (int j = 0; j < arenaSize; j++)
							{
								saveFile << arena[i][j]->objType << "\n" << i << "\n" << j << "\n";
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

						int objType;
						int k;
						int l;;

						while (inFile)
						{

							// read name, x, y, and rotation
							inFile >> objType;
							inFile >> k;
							inFile >> l;

							switch (objType)
							{
							case Ground:
								arena[k][l]->DeleteObject();
								arena[k][l] = new CGround(sf::Vector2f(32 * k + 200, 32 * l));
								break;
							case UnbreakableWall:
								arena[k][l]->DeleteObject();
								arena[k][l] = new CWall(sf::Vector2f(32 * k + 200, 32 * l));
								break;
							default:
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

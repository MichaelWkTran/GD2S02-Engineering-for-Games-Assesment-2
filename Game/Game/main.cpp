#include "CManager.h"
#include "CPlayer.h"
#include "CSpikeTrap.h" 
#include "CTurret.h"
#include "CWall.h"
#include "CWinScene.h"
#include "CHealthBar.h"
#include "CWeaponBox.h"
#include "CWeaponUI.h"
#include "CMenu.h"
#include "CMapSelector.h"
#include <iostream>

bool CMenu::playGame = false;
bool CMenu::controlsScreen = false;
bool CMenu::mapSelectScreen = false;
bool CMenu::settingsScreen = false;

int main()
{
	// seed the time
	srand((unsigned int)time(NULL));

	CManager* manager = new CManager();

	CMenu* menu = new CMenu();
	CMapSelector* mapSelector = new CMapSelector;
	//CPlayer* player1 = new CPlayer(sf::Keyboard::W, sf::Keyboard::S, sf::Keyboard::A, sf::Keyboard::D, sf::Keyboard::V, { 800, 200 }, true);
	//CPlayer* player2 = new CPlayer(sf::Keyboard::Up, sf::Keyboard::Down, sf::Keyboard::Left, sf::Keyboard::Right, sf::Keyboard::Slash, { 800, 500 }, false);
	//manager->players[0] = player1;
	//manager->players[1] = player2;
	CWinScene* winScene = new CWinScene();
	/*CWeaponBox* weaponBox1 = new CWeaponBox(sf::Vector2f(900.f, 300.f));
	CWeaponBox* weaponBox2 = new CWeaponBox(sf::Vector2f(1000.f, 300.f));
	CWeaponBox* weaponBox3 = new CWeaponBox(sf::Vector2f(1100.f, 300.f));
	CWeaponBox* weaponBox4 = new CWeaponBox(sf::Vector2f(1200.f, 300.f));
	weaponBox1->SetWeapon(0);
	weaponBox2->SetWeapon(1);
	weaponBox3->SetWeapon(2);
	weaponBox4->SetWeapon(3);*/
	
	while (manager->isRunning)
	{
		manager->Update();

	}
}
#include "CManager.h"
#include "CPlayer.h"
#include "CSpikeTrap.h" 
#include "CTurret.h"
#include "CWall.h"
#include "WinScene.h"
#include "CHealthBar.h"
#include "CWeaponBox.h"
#include "CWeaponUI.h"
#include <iostream>

int main()
{
	CManager* manager = new CManager();
	CPlayer* player1 = new CPlayer(sf::Keyboard::W, sf::Keyboard::S, sf::Keyboard::A, sf::Keyboard::D, sf::Keyboard::V, { 800, 200 }, true);
	CPlayer* player2 = new CPlayer(sf::Keyboard::Up, sf::Keyboard::Down, sf::Keyboard::Left, sf::Keyboard::Right, sf::Keyboard::Slash, { 800, 500 }, false);
	WinScene* winScene = new WinScene();
	CHealthBar* p1HealthBar = new CHealthBar(sf::Vector2f(5.f, 625.f), player1);
	CHealthBar* p2HealthBar = new CHealthBar(sf::Vector2f(1125.f, 625.f), player2);
	CWeaponBox* weaponBox1 = new CWeaponBox(sf::Vector2f(900.f, 300.f));
	CWeaponBox* weaponBox2 = new CWeaponBox(sf::Vector2f(1000.f, 300.f));
	CWeaponBox* weaponBox3 = new CWeaponBox(sf::Vector2f(1100.f, 300.f));
	CWeaponBox* weaponBox4 = new CWeaponBox(sf::Vector2f(1200.f, 300.f));
	weaponBox1->SetWeapon(0);
	weaponBox2->SetWeapon(1);
	weaponBox3->SetWeapon(2);
	weaponBox4->SetWeapon(3);
	CWeaponUI* p1WeaponUI = new CWeaponUI(sf::Vector2f(0.f, 645.f), sf::Vector2f(5.f, 655.f), sf::Vector2f(10.f, 695.f), player1);
	CWeaponUI* p2WeaponUI = new CWeaponUI(sf::Vector2f(1125.f, 645.f), sf::Vector2f(1130.f, 655.f), sf::Vector2f(1135.f, 695.f), player2);

	while (manager->isRunning)
	{
		manager->Update();
	}
}
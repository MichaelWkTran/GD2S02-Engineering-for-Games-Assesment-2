#include "CManager.h"
#include "CPlayer.h"
#include "CSpikeTrap.h" 
#include "CTurret.h"
#include "CWall.h"
#include "WinScene.h"
#include <iostream>

int main()
{
	CManager* manager = new CManager();
	CPlayer* player1 = new CPlayer(sf::Keyboard::W, sf::Keyboard::S, sf::Keyboard::A, sf::Keyboard::D, sf::Keyboard::V, { 800, 200 }, true);
	CPlayer* player2 = new CPlayer(sf::Keyboard::Up, sf::Keyboard::Down, sf::Keyboard::Left, sf::Keyboard::Right, sf::Keyboard::Slash, { 800, 500 }, false);
	WinScene* winScene = new WinScene();

	new CTurret;

	while (manager->isRunning)
	{
		manager->Update();
	}
}
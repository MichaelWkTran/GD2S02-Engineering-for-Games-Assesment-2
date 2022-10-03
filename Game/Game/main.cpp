#include "CManager.h"
#include "CPlayer.h"

int main()
{
	CManager* manager = new CManager();
	CPlayer* player1 = new CPlayer(sf::Keyboard::W, sf::Keyboard::S, sf::Keyboard::A, sf::Keyboard::D, sf::Keyboard::V, { 100, 100 }, true);
	CPlayer* player2 = new CPlayer(sf::Keyboard::Up, sf::Keyboard::Down, sf::Keyboard::Left, sf::Keyboard::Right, sf::Keyboard::Slash, { 800, 500 }, false);
	manager->objectsInWorld.push_back(player1);
	manager->objectsInWorld.push_back(player2);
	player1->AddGunToRender();
	player2->AddGunToRender();

	while (manager->isRunning)
	{
		manager->Update();
	}
}
#include "CManager.h"
#include "CPlayer.h"

int main()
{
	CManager* manager = new CManager();
	//* player1 = new CPlayer(sf::Keyboard::W, sf::Keyboard::S, sf::Keyboard::A, sf::Keyboard::D, sf::Keyboard::V, { 400, 200 }, true);
	//CPlayer* player2 = new CPlayer(sf::Keyboard::Up, sf::Keyboard::Down, sf::Keyboard::Left, sf::Keyboard::Right, sf::Keyboard::Slash, { 800, 500 }, false);

	//CHealthBar* p1HealthBar = new CHealthBar(sf::Vector2f(10.f, 40.f), player1);
	//CHealthBar* p2HealthBar = new CHealthBar(sf::Vector2f(1000.f, 40.f), player2);

	while (manager->isRunning)
	{
		manager->Update();
	}
}
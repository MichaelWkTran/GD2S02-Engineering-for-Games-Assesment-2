#include "CManager.h"
#include "CPlayer.h"
#include "CSpikeTrap.h" 


int main()
{
	CManager* manager = new CManager();
	CPlayer* player1 = new CPlayer(sf::Keyboard::W, sf::Keyboard::S, sf::Keyboard::A, sf::Keyboard::D, sf::Keyboard::V, { 400, 200 }, true);
	CPlayer* player2 = new CPlayer(sf::Keyboard::Up, sf::Keyboard::Down, sf::Keyboard::Left, sf::Keyboard::Right, sf::Keyboard::Slash, { 800, 500 }, false);
	new CSpikeTrap(sf::Vector2f(40.0f, 40.0f));

	while (manager->isRunning)
	{
		manager->Update();
	}
}
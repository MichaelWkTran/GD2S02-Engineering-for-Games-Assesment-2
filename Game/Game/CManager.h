#pragma once
#include <SFML/Graphics.hpp>
class CManager
{
private:
	sf::Vector2f* pScreenSize = nullptr;
	sf::View* pView = nullptr;
	sf::RenderWindow* pWindow = nullptr;

	void Zoom(float _fZoomValue);
public:
	bool isRunning;

	CManager();

	void Update();
};


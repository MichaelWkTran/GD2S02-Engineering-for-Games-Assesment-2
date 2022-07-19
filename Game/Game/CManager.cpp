#include "CManager.h"

void CManager::Zoom(float _fZoomValue)
{
	pView->zoom(_fZoomValue);
	pWindow->setView(*pView);
}

CManager::CManager()
{
	isRunning = true;

	// sets up the window
	// sets up the view
	pScreenSize = new sf::Vector2f(1280, 720);
	sf::Vector2f* tempScreenCenter = new sf::Vector2f(0, 0);
	pView = new sf::View(*tempScreenCenter, *pScreenSize);

	// sets up the renderwindow
	pWindow = new sf::RenderWindow(sf::VideoMode((unsigned int)pScreenSize->x, (unsigned int)pScreenSize->y), "Game");
	pWindow->setView(*pView);

	delete tempScreenCenter;
}

void CManager::Update()
{
	sf::Event event;
	while (pWindow->pollEvent(event))
	{
		// closes the window and stops the program when the user presses the x
		if (event.type == sf::Event::Closed)
		{
			pWindow->close();
			isRunning = false;
			return;
		}

		// resize the window
		if (event.type == sf::Event::Resized)
		{
			if (event.type == sf::Event::Resized)
			{
				pView->setSize((float)event.size.width, (float)event.size.height);
				pView->setCenter(0, 0);
				Zoom(pScreenSize->y / event.size.height);
			}
		}
	}
	pWindow->clear();

	pWindow->display();
}

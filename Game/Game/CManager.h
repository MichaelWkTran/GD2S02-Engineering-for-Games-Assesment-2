#pragma once
#include "box2d\box2D.h"
#include <SFML/Graphics.hpp>
#include <deque>

class CUpdatedObject;

class CManager
{
private:
	static CManager* singleton;
	
	// window and view variables
	sf::Vector2f screenSize;
	sf::View view;
	sf::RenderWindow* window = nullptr;
	sf::Event event;
	sf::Clock deltaTimeClock;

	// physics variables
	b2World* physicsWorld;

	void Zoom(float _fZoomValue);

public:
	std::deque<CUpdatedObject*> objectsInWorld;
	bool isRunning;
	float deltatime;
	sf::Font font;

	// physics variables
	float pixelToWorldScale;
	float timeStep;
	float maxFrameTime;
	float accumulatedTime;
	int velocityIterations;
	int positionIterations;

	// methods
	CManager();
	~CManager();

	template <class T>
	T* CreateObject();
	void Clear();

	void Update();

	// get set methods
	static CManager& GetSingleton() { return *singleton; };
	b2World& GetPhysicsWorld() { return *physicsWorld; }
	sf::RenderWindow& GetWindow() { return *window; }
};

template<class T>
inline T* CManager::CreateObject()
{
	objectsInWorld.emplace_back(new T);
	return (T*)objectsInWorld.back();
}

#define GetManager CManager::GetSingleton
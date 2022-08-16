#pragma once
#include "box2d\box2D.h"
#include <SFML/Graphics.hpp>
#include <deque>

class CUpdatedObject;

class CManager
{
private:
	static CManager* singleton;
	std::deque<CUpdatedObject*> objectsInWorld;

	// window and view variables
	sf::Vector2f screenSize;
	sf::View view;
	sf::RenderWindow* window = nullptr;
	sf::Event event;
	sf::Clock deltaTimeClock;

	//Physics Variables
	b2World* physicsWorld;

	void Zoom(float _fZoomValue);

public:
	bool isRunning;
	float deltatime;

	//Physics Variables
	float pixelToWorldScale;
	float timeStep;
	float maxFrameTime;
	float accumulatedTime;
	int velocityIterations;
	int positionIterations;

	//Methods
	CManager();
	~CManager();

	template <class T>
	T* CreateObject();
	void Clear();

	void Update();

	//Get Set Methods
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
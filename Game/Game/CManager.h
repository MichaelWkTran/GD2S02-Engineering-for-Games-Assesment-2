#pragma once
#include "box2d\box2D.h"
#include <SFML/Graphics.hpp>
#include "CLevelMaker.h"
#include <deque>

class CUpdatedObject;

class CManager : public b2ContactListener
{
	friend CUpdatedObject;

private:
	static CManager* singleton;
	std::deque<CUpdatedObject*> objectsInWorld;

	// window and view variables
	sf::Vector2f screenSize;
	sf::View view;
	sf::RenderWindow* window = nullptr;
	sf::Event event;
	sf::Clock deltaTimeClock;

	// physics variables
	b2World* physicsWorld;

	void Zoom(float _fZoomValue);

	//virtual void BeginContact(b2Contact* _contact) override;
	virtual void BeginContact(b2Contact* _contact) override;
	virtual void EndContact(b2Contact* _contact) override;
	virtual void PreSolve(b2Contact* _contact, const b2Manifold* _oldManifold) override;
	virtual void PostSolve(b2Contact* _contact, const b2ContactImpulse* _impulse) override;

	CLevelMaker* levelmaker = nullptr;

public:
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
	CManager(const CManager&) = delete;
	CManager& operator= (const CManager&) = delete;
	
	void DestroyImmediate(CUpdatedObject* _updatedObject);
	void DestroyImmediate(CUpdatedObject*& _updatedObject);
	void DestroyImmediate(unsigned int _index);
	void Clear();
	void Update();

	// get set methods
	static CManager& GetSingleton() { return *singleton; };
	b2World& GetPhysicsWorld() { return *physicsWorld; }
	sf::RenderWindow& GetWindow() { return *window; }
};

#define GetManager CManager::GetSingleton
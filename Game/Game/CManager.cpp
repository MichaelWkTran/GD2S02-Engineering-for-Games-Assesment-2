#include "CManager.h"
#include "CUpdatedObject.h"
#include "CGameObject.h"
#include "CPhysicsBody.h"
#include "box2d\box2D.h"

CManager* CManager::singleton = nullptr;

void CManager::Zoom(float _zoomValue)
{
	view.zoom(_zoomValue);
	window->setView(view);
}

CManager::CManager()
{
	// check singleton
	if (singleton == nullptr) singleton = this;
	else if (singleton != this)
	{
		delete this;
		return;
	}

	// initialize manager
	isRunning = true;
	deltatime = 0.0f;

	// sets up the window
	// sets up the view
	screenSize = sf::Vector2f(1280, 720);
	view.setCenter(0, 0);
	
	// sets up the renderwindow
	window = new sf::RenderWindow(sf::VideoMode(screenSize.x, screenSize.y), "Game");
	event = sf::Event();
	
	// set up physics
	b2Vec2 v2Gravity(0.0, 0.f);
	physicsWorld = new b2World(v2Gravity);
	pixelToWorldScale = 1.0f / 30.0f;
	timeStep = 1 / 60.0f;
	maxFrameTime = 0.25f;
	accumulatedTime = 0.0f;
	velocityIterations = 8;
	positionIterations = 3;
}

CManager::~CManager()
{
	Clear();
	delete physicsWorld;
}

void CManager::Clear()
{
	const int iGameObjectsCount = objectsInWorld.size();
	for (int i = 0; i < iGameObjectsCount; i++)
	{
		delete objectsInWorld.front();
		objectsInWorld.pop_front();
	}
}

void CManager::Update()
{
	// poll events
	while (window->pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
		{
			// closes the window and stops the program when the user presses the x
			window->close();
			isRunning = false;
			return;
		}

		case sf::Event::Resized:
		{
			// resize the window
			view.setSize((float)event.size.width, (float)event.size.height);
			view.setCenter(0, 0);
			Zoom(screenSize.y / event.size.height);
			break;
		}
		}
	}

	// update deltatime
	deltatime = deltaTimeClock.restart().asSeconds();

	// update physics
	float fFrameTime = GetManager().deltatime;
	if (fFrameTime > maxFrameTime) fFrameTime = maxFrameTime;
	accumulatedTime += fFrameTime;

	while (accumulatedTime > timeStep)
	{
		physicsWorld->Step(timeStep, velocityIterations, positionIterations);
		accumulatedTime -= timeStep;
	}

	// update the transforms of physics objects
	for (auto& pUpdatedObject : objectsInWorld)
	{
		CGameObject* pGameObject = dynamic_cast<CGameObject*>(pUpdatedObject);
		if (pGameObject == nullptr) continue;
		if (pGameObject->GetPhysicsBody() == nullptr) continue;

		b2Vec2 bv2Position = pGameObject->GetPhysicsBody()->GetBody().GetPosition();
		pGameObject->transform.setPosition(bv2Position.x / pixelToWorldScale, bv2Position.y / pixelToWorldScale);
		pGameObject->transform.setRotation((pGameObject->GetPhysicsBody()->GetBody().GetAngle() * 180.0f) / b2_pi);
	}

	// clear screen
	window->clear(sf::Color::White);

	// call updated object methods
	for (auto& pUpdatedObject : objectsInWorld) pUpdatedObject->Start();
	for (auto& pUpdatedObject : objectsInWorld) pUpdatedObject->BeginUpdate();
	for (auto& pUpdatedObject : objectsInWorld) pUpdatedObject->Update();
	for (auto& pUpdatedObject : objectsInWorld) pUpdatedObject->EndUpdate();
	for (auto& pUpdatedObject : objectsInWorld) pUpdatedObject->Draw();

	// display drawn objects
	window->display();

	// delete updated objects
	for (int i = 0; i < (int)objectsInWorld.size(); i++)
	{
		if (!objectsInWorld[i]->GetDeleteObject()) continue;

		CUpdatedObject* pDeletedGameObject = objectsInWorld[i];
		objectsInWorld.erase(objectsInWorld.begin() + i);
		delete pDeletedGameObject;
	}
}
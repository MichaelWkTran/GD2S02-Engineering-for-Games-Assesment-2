#include "CManager.h"
#include "CUpdatedObject.h"
#include "CGameObject.h"
#include "CPhysicsBody.h"
#include "box2d\box2D.h"
#include "CPlayer.h"
#include "CBullet.h"
#include "CWall.h"
#include "CSpikeTrap.h"
#include "Level.h"
#include <iostream>

CManager* CManager::singleton = nullptr;

void CManager::Zoom(float _zoomValue)
{
	view.zoom(_zoomValue);
	window->setView(view);
}

void CManager::BeginContact(b2Contact* _contact)
{
	CPhysicsBody* bodyUserDataA = static_cast<CPhysicsBody*>((void*)_contact->GetFixtureA()->GetBody()->GetUserData().pointer);
	CPhysicsBody* bodyUserDataB = static_cast<CPhysicsBody*>((void*)_contact->GetFixtureB()->GetBody()->GetUserData().pointer);
	if (bodyUserDataA == nullptr || bodyUserDataB == nullptr) return;

	bodyUserDataA->BeginContact(bodyUserDataB);
	bodyUserDataB->BeginContact(bodyUserDataA);
}

void CManager::EndContact(b2Contact* _contact)
{
	CPhysicsBody* bodyUserDataA = static_cast<CPhysicsBody*>((void*)_contact->GetFixtureA()->GetBody()->GetUserData().pointer);
	CPhysicsBody* bodyUserDataB = static_cast<CPhysicsBody*>((void*)_contact->GetFixtureB()->GetBody()->GetUserData().pointer);
	if (bodyUserDataA == nullptr || bodyUserDataB == nullptr) return;

	bodyUserDataA->EndContact(bodyUserDataB);
	bodyUserDataB->EndContact(bodyUserDataA);
}

void CManager::PreSolve(b2Contact* _contact, const b2Manifold* _oldManifold)
{
	CPhysicsBody* bodyUserDataA = static_cast<CPhysicsBody*>((void*)_contact->GetFixtureA()->GetBody()->GetUserData().pointer);
	CPhysicsBody* bodyUserDataB = static_cast<CPhysicsBody*>((void*)_contact->GetFixtureB()->GetBody()->GetUserData().pointer);
	if (bodyUserDataA == nullptr || bodyUserDataB == nullptr) return;

	bodyUserDataA->PreSolve(bodyUserDataB, _oldManifold);
	bodyUserDataB->PreSolve(bodyUserDataA, _oldManifold);
}

void CManager::PostSolve(b2Contact* _contact, const b2ContactImpulse* _impulse)
{
	CPhysicsBody* bodyUserDataA = static_cast<CPhysicsBody*>((void*)_contact->GetFixtureA()->GetBody()->GetUserData().pointer);
	CPhysicsBody* bodyUserDataB = static_cast<CPhysicsBody*>((void*)_contact->GetFixtureB()->GetBody()->GetUserData().pointer);
	if (bodyUserDataA == nullptr || bodyUserDataB == nullptr) return;

	bodyUserDataA->PostSolve(bodyUserDataB, _impulse);
	bodyUserDataB->PostSolve(bodyUserDataA, _impulse);
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
	deltaTime = 0.0f;

	// sets up the window
	// sets up the view
	screenSize = sf::Vector2f(1280, 720);
	view.setCenter(0, 0);
	
	// sets up the renderwindow
	window = new sf::RenderWindow(sf::VideoMode(screenSize.x, screenSize.y), "Game");
	event = sf::Event();
	
	// set up physics
	physicsWorld = new b2World(b2Vec2(0.0f, 0.0f));
	pixelToWorldScale = 1.0f / 30.0f;
	timeStep = 1 / 60.0f;
	maxFrameTime = 0.25f;
	accumulatedTime = 0.0f;
	velocityIterations = 8;
	positionIterations = 3;

	physicsWorld->SetContactListener(this);

	font.loadFromFile("fonts/SansSerif.ttf");

	levelMaker = new CLevelMaker();
	Level* level = new Level("Levels/1.txt");
	levelMaker->LoadLevel(level->GetPath());
	delete level;
	level = nullptr;
}

CManager::~CManager()
{
	Clear();
	delete physicsWorld;
}

void CManager::Clear()
{
	const int objectsCount = objectsInWorld.size();
	for (int i = 0; i < objectsCount; i++)
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

	// update deltaTime
	deltaTime = deltaTimeClock.restart().asSeconds();

	// update physics
	float frameTime = GetManager().deltaTime;
	if (frameTime > maxFrameTime) frameTime = maxFrameTime;
	accumulatedTime += frameTime;

	while (accumulatedTime > timeStep)
	{
		physicsWorld->Step(timeStep, velocityIterations, positionIterations);
		accumulatedTime -= timeStep;
	}

	// update the transforms of physics objects
	for (auto& pUpdatedObject : objectsInWorld)
	{
		CGameObject* gameObject = dynamic_cast<CGameObject*>(pUpdatedObject);
		CPhysicsBody* physicsBody = dynamic_cast<CPhysicsBody*>(pUpdatedObject);

		if (gameObject == nullptr) continue;
		if (physicsBody == nullptr) continue;

		b2Vec2 bv2Position = physicsBody->GetBody().GetPosition();
		gameObject->transform.setPosition(bv2Position.x / pixelToWorldScale, bv2Position.y / pixelToWorldScale);
		gameObject->transform.setRotation((physicsBody->GetBody().GetAngle() * 180.0f) / b2_pi);
	}

	// clear screen
	window->clear(sf::Color::White);
	levelMaker->Update();

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
		// ignore objects that have not been tagged for deletion
		if (!objectsInWorld[i]->GetDeleteObject()) continue;

		// delete the object
		CUpdatedObject* deletedObject = objectsInWorld[i];
		objectsInWorld.erase(objectsInWorld.begin() + i);
		delete deletedObject;
		i--;
	}
}
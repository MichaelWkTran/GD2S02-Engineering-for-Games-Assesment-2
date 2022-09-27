#include "CManager.h"
#include "CUpdatedObject.h"
#include "CGameObject.h"
#include "CPhysicsBody.h"
#include "box2d\box2D.h"
#include "CPlayer.h"
#include "CBullet.h"
#include "CWall.h"
#include "CSpikeTrap.h"
#include <iostream>

CManager* CManager::singleton = nullptr;

void CManager::Zoom(float _zoomValue)
{
	view.zoom(_zoomValue);
	window->setView(view);
}

void CManager::BeginContact(b2Contact* _contact)
{
	//Get data of collided objects if it exists.
	CPhysicsBody* bodyUserDataA = static_cast<CPhysicsBody*>((void*)_contact->GetFixtureA()->GetBody()->GetUserData().pointer);
	CPhysicsBody* bodyUserDataB = static_cast<CPhysicsBody*>((void*)_contact->GetFixtureB()->GetBody()->GetUserData().pointer);
	if (bodyUserDataA == nullptr || bodyUserDataB == nullptr) return;

	//Call BeginContact() from the data found. 
	bodyUserDataA->BeginContact(bodyUserDataB);
	bodyUserDataB->BeginContact(bodyUserDataA);
}

void CManager::EndContact(b2Contact* _contact)
{
	//Get data of collided objects if it exists.
	CPhysicsBody* bodyUserDataA = (CPhysicsBody*)_contact->GetFixtureA()->GetBody()->GetUserData().pointer;
	CPhysicsBody* bodyUserDataB = (CPhysicsBody*)_contact->GetFixtureB()->GetBody()->GetUserData().pointer;
	if (bodyUserDataA == nullptr || bodyUserDataB == nullptr) return;

	//Call EndContact() from the data found. 
	bodyUserDataA->EndContact(bodyUserDataB);
	bodyUserDataB->EndContact(bodyUserDataA);
}

void CManager::PreSolve(b2Contact* _contact, const b2Manifold* _oldManifold)
{
	//Get data of collided objects if it exists.
	CPhysicsBody* bodyUserDataA = (CPhysicsBody*)_contact->GetFixtureA()->GetBody()->GetUserData().pointer;
	CPhysicsBody* bodyUserDataB = (CPhysicsBody*)_contact->GetFixtureB()->GetBody()->GetUserData().pointer;
	if (bodyUserDataA == nullptr || bodyUserDataB == nullptr) return;

	//Call PreSolve() from the data found. 
	bodyUserDataA->PreSolve(bodyUserDataB, _oldManifold);
	bodyUserDataB->PreSolve(bodyUserDataA, _oldManifold);
}

void CManager::PostSolve(b2Contact* _contact, const b2ContactImpulse* _impulse)
{
	//Get data of collided objects if it exists.
	CPhysicsBody* bodyUserDataA = (CPhysicsBody*)_contact->GetFixtureA()->GetBody()->GetUserData().pointer;
	CPhysicsBody* bodyUserDataB = (CPhysicsBody*)_contact->GetFixtureB()->GetBody()->GetUserData().pointer;
	if (bodyUserDataA == nullptr || bodyUserDataB == nullptr) return;

	//Call PostSolve() from the data found. 
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

	physicsWorld->SetContactListener(this);

	font.loadFromFile("fonts/SansSerif.ttf");

	levelmaker = new CLevelMaker();
}

CManager::~CManager()
{
	Clear();
	delete physicsWorld;
}

void CManager::DestroyImmediate(CUpdatedObject*&& _updatedObject)
{
	// check whether the given object is valid
	if (_updatedObject == nullptr)
	{
		std::cout << "ERROR: Can not use DestroyImmediate on nullptr";
		return;
	}

	// seach though m_dequeUpdatedObject to find the object and delete it
	for (int i = 0; i < (int)objectsInWorld.size(); i++)
	{
		if (objectsInWorld[i] != _updatedObject) continue;

		objectsInWorld.erase(objectsInWorld.begin() + i);
		delete _updatedObject;

		return;
	}
}

void CManager::DestroyImmediate(CUpdatedObject*& _updatedObject)
{
	// check whether the given object is valid
	if (_updatedObject == nullptr)
	{
		std::cout << "ERROR: Can not use DestroyImmediate on nullptr";
		return;
	}

	// seach though objectsInWorld to find the object and delete it
	for (int i = 0; i < (int)objectsInWorld.size(); i++)
	{
		if (objectsInWorld[i] != _updatedObject) continue;

		objectsInWorld.erase(objectsInWorld.begin() + i);
		delete _updatedObject;

		// ensure that the given pointer refrence is set to nullptr
		_updatedObject = nullptr;

		return;
	}
}

void CManager::DestroyImmediate(unsigned int _index)
{
	//Get the object to be deleted
	CUpdatedObject* pUpdatedObject = objectsInWorld[_index];

	//Delete the object and remove it from objectsInWorld
	objectsInWorld.erase(objectsInWorld.begin() + _index);
	delete pUpdatedObject;
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
	for (auto& updatedObject : objectsInWorld)
	{
		CGameObject* gameObject = dynamic_cast<CGameObject*>(updatedObject);
		CPhysicsBody* physicsBody = dynamic_cast<CPhysicsBody*>(updatedObject);

		if (gameObject == nullptr) continue;
		if (physicsBody == nullptr) continue;

		b2Vec2 position = physicsBody->GetBody().GetPosition();
		gameObject->transform.setPosition(position.x / pixelToWorldScale, position.y / pixelToWorldScale);
		gameObject->transform.setRotation((physicsBody->GetBody().GetAngle() * 180.0f) / b2_pi);
	}

	// clear screen
	window->clear(sf::Color::White);
	levelmaker->Update();

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

		DestroyImmediate(i);
		i--;
	}
}
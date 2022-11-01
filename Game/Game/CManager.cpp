// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
// (c) 2022 Media Design School
//
// File Name: CManager.cpp
// Description: CManager declaration file
// Authors: Michael Wai Kit Tran

#include "CManager.h"
#include "CUpdatedObject.h"
#include "CGameObject.h"
#include "CPhysicsBody.h"
#include "CWall.h"
#include "box2d\box2D.h"
#include "CPlayer.h"
#include "CLevel.h"
#include "CWinScene.h"
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
	timeScale = 1.0f;
	soundVolume = 100.0f;

	// sets up the window
	// sets up the view
	screenSize = sf::Vector2f(1280, 720);
	view.setCenter(0, 0);
	
	// sets up the renderwindow
	window = new sf::RenderWindow(sf::VideoMode((unsigned int)screenSize.x, (unsigned int)screenSize.y), "King of the Arena");
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

	font.loadFromFile("fonts/ARCADE.TTF");

	levelMaker = new CLevelMaker();
}

CManager::~CManager()
{
	Clear();
	delete physicsWorld;
}

void CManager::PlaceObjectAtFront(CUpdatedObject* _object)
{
	for (int i = 0; i < objectsInWorld.size(); i++)
	{
		if (objectsInWorld[i] == _object)
		{
			objectsInWorld.erase(objectsInWorld.begin() + i);
			objectsInWorld.push_front(_object);
		}
	}
}

void CManager::Clear()
{
	const int objectsCount = (int)objectsInWorld.size();
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
			view.setCenter(screenSize/2.0f);
			Zoom(screenSize.y / event.size.height);
			break;
		}
		}
	}

	// update deltaTime
	deltaTime = deltaTimeClock.restart().asSeconds() * timeScale;

	//Freeze game if the window is not focused
	if (!window->hasFocus()) return;

	// update physics
	float frameTime = GetManager().deltaTime;
	if (frameTime > maxFrameTime) frameTime = maxFrameTime;
	accumulatedTime += frameTime;

	while (accumulatedTime > timeStep)
	{
		accumulatedTime -= timeStep;
		
		// update physics world
		physicsWorld->Step(timeStep, velocityIterations, positionIterations);
		
		// call physics object methods
		for (auto& updatedObject : objectsInWorld)
		{
			CPhysicsBody* physicsBody = dynamic_cast<CPhysicsBody*>(updatedObject);
			if (physicsBody != nullptr) physicsBody->FixedUpdate();
		}
	}

	// update the transforms of physics objects
	for (auto& updatedObject : objectsInWorld)
	{
		CGameObject* gameObject = dynamic_cast<CGameObject*>(updatedObject);
		CPhysicsBody* physicsBody = dynamic_cast<CPhysicsBody*>(updatedObject);

		if (gameObject == nullptr) continue;
		if (physicsBody == nullptr) continue;

		b2Vec2 bv2Position = physicsBody->GetBody().GetPosition();
		gameObject->transform.setPosition(bv2Position.x / pixelToWorldScale, bv2Position.y / pixelToWorldScale);
		gameObject->transform.setRotation((physicsBody->GetBody().GetAngle() * 180.0f) / b2_pi);
	}

	// clear screen
	window->clear(sf::Color(255, 136, 77, 255));
	if (spawnWeapons)
	{
		counterWeaponSpawnTime += deltaTime;
		if (counterWeaponSpawnTime >= weaponSpawnTime)
		{
			levelMaker->SpawnWeaponBox();
			counterWeaponSpawnTime = 0.0f;
		}
	}

	// call updated object methods
	for (auto& updatedObject : objectsInWorld) updatedObject->Start();
	for (auto& updatedObject : objectsInWorld) updatedObject->BeginUpdate();
	for (auto& updatedObject : objectsInWorld) updatedObject->Update();
	for (auto& updatedObject : objectsInWorld) updatedObject->EndUpdate();
	for (auto& updatedObject : objectsInWorld) updatedObject->Draw();

	// display drawn objects
	window->display();

	// delete updated objects
	for (int i = 0; i < (int)objectsInWorld.size(); i++)
	{
		if (dynamic_cast<CMapPlaceBase*>(objectsInWorld[i]) && levelMaker->shouldDelete)
		{
			objectsInWorld[i]->DeleteObject();
		}
		// ignore objects that have not been tagged for deletion
		if (!objectsInWorld[i]->GetDeleteObject()) continue;

		// delete the object
		CUpdatedObject* deletedObject = objectsInWorld[i];
		objectsInWorld.erase(objectsInWorld.begin() + i);
		delete deletedObject;
		i--;
	}
}

void CManager::ResetWeaponTimer()
{
	counterWeaponSpawnTime = 0;
}

void CManager::LoadNewLevel(std::string _path)
{
	CLevel* level = new CLevel("Levels/" + _path + ".txt");
	levelMaker->LoadLevel(level->GetPath());
	delete level;
	level = nullptr;
	ResetPlayers();
}

void CManager::ResetPlayers()
{
	for (int i = 0; i < 2; i++)
	{
		if (players[i] != nullptr)
		{
			players[i]->Kill();
		}
	}
	// create new player 1 object
	players[0] = new CPlayer(sf::Keyboard::W, sf::Keyboard::S, sf::Keyboard::A,
		sf::Keyboard::D, sf::Keyboard::V, levelMaker->playerSpawns[0], true);
	// create new player 2 object
	players[1] = new CPlayer(sf::Keyboard::Up, sf::Keyboard::Down, sf::Keyboard::Left,
		sf::Keyboard::Right, sf::Keyboard::Slash, levelMaker->playerSpawns[1], false);
}

void CManager::SetPlayerReferanceNull(CPlayer* _player)
{
	for (int i = 0; i < 2; i++)
	{
		if (players[i] == _player)
		{
			players[i] = nullptr;
		}
	}
}

void CManager::ReplaceWithGround(CWall* _block)
{
	levelMaker->ReplaceWithGround(_block);
}

void CManager::SetVolume(float _volume)
{
	soundVolume = _volume;
}

float CManager::GetVolume()
{
	return soundVolume;
}

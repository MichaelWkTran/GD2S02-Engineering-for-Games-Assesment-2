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
	CPhysicsBody* pBodyUserDataA = static_cast<CPhysicsBody*>((void*)_contact->GetFixtureA()->GetBody()->GetUserData().pointer);
	CPhysicsBody* pBodyUserDataB = static_cast<CPhysicsBody*>((void*)_contact->GetFixtureB()->GetBody()->GetUserData().pointer);
	if (pBodyUserDataA == nullptr || pBodyUserDataB == nullptr) return;

	pBodyUserDataA->BeginContact(pBodyUserDataB);
	pBodyUserDataB->BeginContact(pBodyUserDataA);
}

void CManager::EndContact(b2Contact* _contact)
{
	CPhysicsBody* pBodyUserDataA = static_cast<CPhysicsBody*>((void*)_contact->GetFixtureA()->GetBody()->GetUserData().pointer);
	CPhysicsBody* pBodyUserDataB = static_cast<CPhysicsBody*>((void*)_contact->GetFixtureB()->GetBody()->GetUserData().pointer);
	if (pBodyUserDataA == nullptr || pBodyUserDataB == nullptr) return;

	pBodyUserDataA->EndContact(pBodyUserDataB);
	pBodyUserDataB->EndContact(pBodyUserDataA);
}

void CManager::PreSolve(b2Contact* _contact, const b2Manifold* _pOldManifold)
{
	CPhysicsBody* pBodyUserDataA = static_cast<CPhysicsBody*>((void*)_contact->GetFixtureA()->GetBody()->GetUserData().pointer);
	CPhysicsBody* pBodyUserDataB = static_cast<CPhysicsBody*>((void*)_contact->GetFixtureB()->GetBody()->GetUserData().pointer);
	if (pBodyUserDataA == nullptr || pBodyUserDataB == nullptr) return;

	pBodyUserDataA->PreSolve(pBodyUserDataB, _pOldManifold);
	pBodyUserDataB->PreSolve(pBodyUserDataA, _pOldManifold);
}

void CManager::PostSolve(b2Contact* _contact, const b2ContactImpulse* _pImpulse)
{
	CPhysicsBody* pBodyUserDataA = static_cast<CPhysicsBody*>((void*)_contact->GetFixtureA()->GetBody()->GetUserData().pointer);
	CPhysicsBody* pBodyUserDataB = static_cast<CPhysicsBody*>((void*)_contact->GetFixtureB()->GetBody()->GetUserData().pointer);
	if (pBodyUserDataA == nullptr || pBodyUserDataB == nullptr) return;

	pBodyUserDataA->PostSolve(pBodyUserDataB, _pImpulse);
	pBodyUserDataB->PostSolve(pBodyUserDataA, _pImpulse);
}

//void CManager::BeginContact(b2Contact* _contact)
//{
//	CPhysicsBody* objectOne = (CPhysicsBody*)_contact->GetFixtureA()->GetBody()->GetUserData().pointer;
//	CPhysicsBody* objectTwo = (CPhysicsBody*)_contact->GetFixtureB()->GetBody()->GetUserData().pointer;
//	if (objectOne == nullptr || objectTwo == nullptr) return;
//
//	if (dynamic_cast<CGameObject*>(objectOne) && dynamic_cast<CGameObject*>(objectTwo))
//	{
//		//Player Bullet Collision
//		if (dynamic_cast<CGameObject*>(objectOne)->TagExists("Player") && dynamic_cast<CGameObject*>(objectTwo)->TagExists("Bullet"))
//		{
//			dynamic_cast<CPlayer*>(objectOne)->TakeDamage(dynamic_cast<CBullet*>(objectTwo)->damage);
//			dynamic_cast<CGameObject*>(objectTwo)->DeleteObject();
//		}
//		//Bullet Player Collision
//		else if (dynamic_cast<CGameObject*>(objectOne)->TagExists("Bullet") && dynamic_cast<CGameObject*>(objectTwo)->TagExists("Player"))
//		{
//			dynamic_cast<CPlayer*>(objectTwo)->TakeDamage(dynamic_cast<CBullet*>(objectOne)->damage);
//			dynamic_cast<CGameObject*>(objectOne)->DeleteObject();
//		}
//		//Bullet Wall Collision
//		else if (dynamic_cast<CGameObject*>(objectOne)->TagExists("Bullet") && dynamic_cast<CGameObject*>(objectTwo)->TagExists("Wall"))
//		{
//			dynamic_cast<CWall*>(objectTwo)->TakeDamage(dynamic_cast<CBullet*>(objectOne)->damage);
//			dynamic_cast<CGameObject*>(objectOne)->DeleteObject();
//		}
//		//Wall Bullet Collision
//		else if (dynamic_cast<CGameObject*>(objectOne)->TagExists("Wall") && dynamic_cast<CGameObject*>(objectTwo)->TagExists("Bullet"))
//		{
//			dynamic_cast<CWall*>(objectOne)->TakeDamage(10.0f);
//			dynamic_cast<CGameObject*>(objectTwo)->DeleteObject();
//		}
//		//Player SpikeTrap Collision
//		else if (dynamic_cast<CGameObject*>(objectOne)->TagExists("Player") && dynamic_cast<CGameObject*>(objectTwo)->TagExists("SpikeTrap"))
//		{
//			dynamic_cast<CPlayer*>(objectOne)->TakeDamage(dynamic_cast<CSpikeTrap*>(objectTwo)->damage);
//		}
//		//SpikeTrap Player Collision
//		else if (dynamic_cast<CGameObject*>(objectOne)->TagExists("SpikeTrap") && dynamic_cast<CGameObject*>(objectTwo)->TagExists("Player"))
//		{
//			dynamic_cast<CPlayer*>(objectTwo)->TakeDamage(dynamic_cast<CSpikeTrap*>(objectOne)->damage);
//		}
//	}
//}

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

void CManager::DestroyImmediate(CUpdatedObject* _UpdatedObject)
{
	if (_UpdatedObject == nullptr)
	{
		std::cout << "ERROR: Can not use DestroyImmediate on nullptr";
		return;
	}

	for (int i = 0; i < (int)objectsInWorld.size(); i++)
	{
		if (objectsInWorld[i] != _UpdatedObject) continue;

		objectsInWorld.erase(objectsInWorld.begin() + i);
		delete _UpdatedObject;

		return;
	}
}

void CManager::DestroyImmediate(CUpdatedObject*& _UpdatedObject)
{
	if (_UpdatedObject == nullptr)
	{
		std::cout << "ERROR: Can not use DestroyImmediate on nullptr";
		return;
	}

	for (int i = 0; i < (int)objectsInWorld.size(); i++)
	{
		if (objectsInWorld[i] != _UpdatedObject) continue;

		objectsInWorld.erase(objectsInWorld.begin() + i);
		delete _UpdatedObject;
		_UpdatedObject = nullptr;

		return;
	}
}

void CManager::DestroyImmediate(unsigned int _uiIndex)
{
	CUpdatedObject* updatedObject = objectsInWorld[_uiIndex];

	objectsInWorld.erase(objectsInWorld.begin() + _uiIndex);
	delete updatedObject;
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
		CPhysicsBody* pPhysicsBody = dynamic_cast<CPhysicsBody*>(pUpdatedObject);

		if (pGameObject == nullptr) continue;
		if (pPhysicsBody == nullptr) continue;

		b2Vec2 bv2Position = pPhysicsBody->GetBody().GetPosition();
		pGameObject->transform.setPosition(bv2Position.x / pixelToWorldScale, bv2Position.y / pixelToWorldScale);
		pGameObject->transform.setRotation((pPhysicsBody->GetBody().GetAngle() * 180.0f) / b2_pi);
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

		CUpdatedObject* pDeletedGameObject = objectsInWorld[i];
		objectsInWorld.erase(objectsInWorld.begin() + i);
		//if (((CGameObject*)pDeletedGameObject)->GetPhysicsBody() != nullptr)
		//{
		//	physicsWorld->DestroyBody(&((CGameObject*)pDeletedGameObject)->GetPhysicsBody()->GetBody());
		//}
		delete pDeletedGameObject;


		//if (!objectsInWorld[i]->GetDeleteObject()) continue;

		//DestroyImmediate(i);
		i--;
	}
}
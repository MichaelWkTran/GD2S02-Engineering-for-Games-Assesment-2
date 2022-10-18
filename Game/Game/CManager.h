// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
// (c) 2022 Media Design School
//
// File Name: CManager.h
// Description: CManager initialization file
// Authors: Michael Wai Kit Tran

#pragma once
#include "box2d\box2D.h"
#include <SFML/Graphics.hpp>
#include "CLevelMaker.h"
#include <deque>

class CUpdatedObject;
class CPlayer;
class CWeaponBox;
class CWall;

class CManager : public b2ContactListener
{
	friend CUpdatedObject;

private:
	static CManager* singleton;
	std::deque<CUpdatedObject*> objectsInWorld;

	float weaponSpawnTime = 10.0f;
	float counterWeaponSpawnTime = 0.0f;

	// window and view variables
	sf::Vector2f screenSize;
	sf::View view;
	sf::RenderWindow* window = nullptr;
	sf::Event event;
	sf::Clock deltaTimeClock;

	// physics variables
	b2World* physicsWorld;

	void Zoom(float _zoomValue);

	virtual void BeginContact(b2Contact* _contact) override;
	virtual void EndContact(b2Contact* _contact) override;
	virtual void PreSolve(b2Contact* _contact, const b2Manifold* _oldManifold) override;
	virtual void PostSolve(b2Contact* _contact, const b2ContactImpulse* _impulse) override;

public:

	// player referances
	CPlayer* players[2];

	std::vector<CWeaponBox*> weaponBoxes;
	int maxBoxes = 10;

	CLevelMaker* levelMaker = nullptr;

	bool isRunning;
	float deltaTime;
	float timeScale;
	bool spawnWeapons = false;
	sf::Font font;

	// physics variables
	float pixelToWorldScale;
	float timeStep;
	float maxFrameTime;
	float accumulatedTime;
	int velocityIterations;
	int positionIterations;
	float soundVolume = 1.f;

	// methods
	CManager();
	~CManager();
	CManager(const CManager&) = delete;
	CManager& operator= (const CManager&) = delete;
	
	void PlaceObjectAtFront(CUpdatedObject* _object);
	void Clear();
	void Update();
	void ResetWeaponTimer();
	void LoadNewLevel(std::string _path);
	void ResetPlayers();
	void SetPlayerReferanceNull(CPlayer* _player);

	void ReplaceWithGround(CWall* _block);

	// get set methods
	static CManager& GetSingleton() { return *singleton; };
	b2World& GetPhysicsWorld() { return *physicsWorld; };
	sf::RenderWindow& GetWindow() { return *window; };
	void SetVolume(float _volume);
	float GetVolume();
};

#define GetManager CManager::GetSingleton
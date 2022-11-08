// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
// (c) 2022 Media Design School
//
// File Name: CWall.h
// Description: CWall initialization file
// Authors: Michael Wai Kit Tran

#pragma once
#include "CMapPlaceBase.h"
#include "CPhysicsBody.h"

class CWall : public CPhysicsBody, public CMapPlaceBase
{
public:
	static std::shared_ptr<sf::Texture> breakableWallTexture;
	static std::shared_ptr<sf::Texture> breakableWallTexture1;
	static std::shared_ptr<sf::Texture> breakableWallTexture2;
	static std::shared_ptr<sf::Texture> unbreakableWallTexture;

	sf::RectangleShape* rectangleShape;// = (sf::RectangleShape*)drawable;

	bool isBreakable;
	float health;

	CWall(sf::Vector2f _pos, float _rotation, bool _isBreakable = false);

	virtual void BeginContact(CPhysicsBody* _other);
};
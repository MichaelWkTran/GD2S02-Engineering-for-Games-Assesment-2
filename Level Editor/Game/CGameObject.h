#pragma once
#include "CUpdatedObject.h"
#include <SFML/Graphics.hpp>
#include <set>
#include <memory>

class CPhysicsBody;

class CGameObject : public CUpdatedObject
{
protected:
	//Physics
	CPhysicsBody* physicsBody;

	//Drawing Variables
	sf::Drawable* drawable;

public:
	//Refrencing Variables
	std::set<const char*> tags;

	//Transform Variables
	sf::Transformable transform;

	//Drawing Variables
	std::shared_ptr<sf::Texture> texture;
	bool visible;

	//GameObject Methods
	CGameObject()
	{
		physicsBody = nullptr;
		drawable = nullptr;
		visible = true;
	}
	~CGameObject();
	const bool TagExists(const char* _tagName)
	{
		if (tags.find(_tagName) != tags.end()) return true;
		else return false;
	}
	virtual void Draw() override;

	//Get Set Methods
	CPhysicsBody* GetPhysicsBody() { return physicsBody; }
	sf::Drawable* GetDrawable() { return drawable; }
};
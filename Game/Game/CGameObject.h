#pragma once
#include "CUpdatedObject.h"
#include <SFML/Graphics.hpp>
#include <set>
#include <memory>

class CGameObject : public CUpdatedObject
{
protected:
	// drawing variables
	sf::Drawable* drawable;

public:
	// refrencing variables
	std::set<const char*> tags;

	// transform variables
	sf::Transformable transform;

	// drawing variables
	std::shared_ptr<sf::Texture> texture;
	bool visible;

	// gameObject methods
	CGameObject()
	{
		drawable = nullptr;
		visible = true;
	}
	virtual ~CGameObject();
	const bool TagExists(const char* _tagName)
	{
		if (tags.find(_tagName) != tags.end()) return true;
		else return false;
	}
	virtual void Draw() override;

	// get set methods
	sf::Drawable* GetDrawable() { return drawable; }
};
#include "CGameObject.h"
#include "CManager.h"
#include <SFML/Graphics.hpp>
#include <iostream>

CGameObject::~CGameObject()
{
	if (drawable != nullptr) delete drawable;
};

void CGameObject::Draw()
{
	if (!visible) return;

	// transform the drawable to transform
	sf::Transformable* drawableTransform = dynamic_cast<sf::Transformable*>(drawable);
	if (drawableTransform == nullptr)
	{
		std::cout << "ERROR: m_pDrawable in CGameObject must inherit from sf::Transformable\n";
		return;
	}

	drawableTransform->setPosition(transform.getPosition());
	drawableTransform->setScale(transform.getScale());
	drawableTransform->setRotation(transform.getRotation());
	drawableTransform->setOrigin(transform.getOrigin());

	// draw drawable
	GetManager().GetWindow().draw(*drawable);
}
#include "CGameObject.h"
#include "CManager.h"
#include <SFML/Graphics.hpp>
#include <iostream>

CGameObject::~CGameObject()
{
	if (physicsBody != nullptr) delete physicsBody;
	if (drawable != nullptr) delete drawable;
};

void CGameObject::Draw()
{
	if (!visible) return;

	//Transform the drawable to m_Transfrom
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

	//Draw Drawable
	GetManager().GetWindow().draw(*drawable);
}
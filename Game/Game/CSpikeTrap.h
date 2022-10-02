#pragma once
#include "CGameObject.h"

class CSpikeTrap : public CGameObject
{
public:
	static float damage;

	CSpikeTrap(sf::Vector2f _pos);
	virtual void Update() override;
};


#pragma once
#include "CMapPlaceBase.h"

class CWall : public CMapPlaceBase
{
public:
	float health;

	CWall(sf::Vector2f _pos);
	~CWall();

	virtual void Update() override;
};
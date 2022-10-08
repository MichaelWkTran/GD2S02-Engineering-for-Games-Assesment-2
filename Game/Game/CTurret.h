#pragma once
#include "CGameObject.h"
#include "CMapPlaceBase.h"

class CTurret : public CMapPlaceBase
{
public:
	static float bulletDamage;
	static float bulletSpeed;
	static float coolDown;
	static float sightDistance;

	float coolDownTimer;

	CTurret();
	CTurret(sf::Vector2f _pos);
	virtual ~CTurret();

	virtual void Update() override;
};


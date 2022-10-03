#pragma once
#include "CGameObject.h"

class CTurret : public CGameObject
{
public:
	static float bulletDamage;
	static float bulletSpeed;
	static float coolDown;
	static float sightDistance;

	float coolDownTimer;

	CTurret();
	virtual ~CTurret();

	virtual void Update() override;
};


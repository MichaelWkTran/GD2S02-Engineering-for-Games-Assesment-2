#pragma once
#include "CGameObject.h"
#include "CPhysicsBody.h"

class CTurret : public CPhysicsBody, public CGameObject
{
public:
	static float bulletDamage;
	static float bulletSpeed;
	static float coolDown;
	static float sightDistance;

	float coolDownTimer;

	CTurret();
	~CTurret();

	virtual void Update() override;
};


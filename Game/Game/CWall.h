#pragma once
#include "CGameObject.h"

class CWall : public CGameObject
{
public:
	float health;

	CWall();
	~CWall();

	virtual void Update() override;
};
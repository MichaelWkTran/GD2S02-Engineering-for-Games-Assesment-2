#pragma once
#include "CGameObject.h"
class CWeaponUI : public CGameObject
{
private:
	sf::Texture weaponTexture;
	sf::RectangleShape uiBox;
	sf::Text uiText;

public:
	CWeaponUI();
	~CWeaponUI();
	void Update();
};


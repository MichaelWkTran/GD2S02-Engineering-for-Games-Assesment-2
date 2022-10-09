// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
// (c) 2022 Media Design School
//
// File Name: CUpdatedObject.cpp
// Description: CUpdatedObject declaration file
// Authors: Michael Wai Kit Tran

#include "CUpdatedObject.h"
#include "CManager.h"

CUpdatedObject::CUpdatedObject()
{
	startCalled = false;
	deleteUpdatedObject = false;
	GetManager().objectsInWorld.emplace_back(this);
}
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
// (c) 2022 Media Design School
//
// File Name: CUpdatedObject.h
// Description: CUpdatedObject initialization file
// Authors: Michael Wai Kit Tran

#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
class CManager;

class CUpdatedObject
{
private:
	bool startCalled;
	bool deleteUpdatedObject;

public:
	CUpdatedObject();
	virtual ~CUpdatedObject() {}

	const bool GetDeleteObject() const
	{
		return deleteUpdatedObject;
	}
	void DeleteObject()
	{
		deleteUpdatedObject = true;
	}

	virtual void Start()
	{
		if (startCalled) return;
		startCalled = true;
	};
	virtual void BeginUpdate() {}
	virtual void Update() {}
	virtual void EndUpdate() {}
	virtual void Draw() {};
};
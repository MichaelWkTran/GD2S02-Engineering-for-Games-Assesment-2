#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
class CManager;

class CUpdatedObject
{
private:
	bool startCalled;
	bool deleteUpdatedObject;

public:
	CUpdatedObject()
	{
		startCalled = false;
		deleteUpdatedObject = false;
	}

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
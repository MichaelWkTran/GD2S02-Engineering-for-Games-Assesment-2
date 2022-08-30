#include "CUpdatedObject.h"
#include "CManager.h"

CUpdatedObject::CUpdatedObject()
{
	startCalled = false;
	deleteUpdatedObject = false;
	GetManager().objectsInWorld.emplace_back(this);
}
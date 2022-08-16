#include "CManager.h"
#include "CPlayer.h"

int main()
{
	CManager* manager = new CManager();
	manager->CreateObject<CPlayer>();

	while (manager->isRunning)
	{
		manager->Update();
	}
}
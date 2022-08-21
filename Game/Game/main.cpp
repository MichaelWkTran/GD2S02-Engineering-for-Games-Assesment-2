#include "CManager.h"
#include "CPlayer.h"

int main()
{
	CManager* manager = new CManager();
	CPlayer* player = manager->CreateObject<CPlayer>();
	player->AddGunToRender();

	while (manager->isRunning)
	{
		manager->Update();
	}
}
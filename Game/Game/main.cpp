#include "CManager.h"
#include "CPlayer.h"

int main()
{
	CManager* pManager = new CManager();
	pManager->CreateObject<CPlayer>();

	while (pManager->isRunning)
	{
		pManager->Update();
	}
}
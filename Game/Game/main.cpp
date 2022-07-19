#include "CManager.h"

int main()
{
	CManager* pManager = new CManager();

	while (pManager->isRunning)
	{
		pManager->Update();
	}
}
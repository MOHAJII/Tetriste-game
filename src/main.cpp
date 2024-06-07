#include "GameManager.h"
	
int main(int argc, char *argv[])
{
	QuickSDL::GameManager *Game = QuickSDL::GameManager::Instance();
	Game->Run();

	QuickSDL::GameManager::Release();
	Game = NULL;

	return 0;
}
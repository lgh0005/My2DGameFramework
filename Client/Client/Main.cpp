#include "pch.h"
#include "Main.h"

int SDL_main(int, char**)
{
	GAME->Init();
	GAME->Launch();

	return 0;
}
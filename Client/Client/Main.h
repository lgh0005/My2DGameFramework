#pragma once

Game game;

int SDL_main(int, char**)
{
	game.Init();
	game.Launch();

	return 0;
}
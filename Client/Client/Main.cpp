#include "pch.h"
#include "Main.h"

int SDL_main(int, char**)
{
	// Game content scenes
	vector<shared_ptr<Scene>> SCENES
	{
		make_shared<DevScene>("DevScene"),
		make_shared<TestScene>("TestScene")
	};

	// Run game application
	LAUNCH->AddScenes(SCENES);
	LAUNCH->Run("DevScene");

	return 0;
}
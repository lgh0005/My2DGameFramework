#include "pch.h"
#include "InGame.h"

InGame::InGame(const string& name) : Super(name)
{

}

void InGame::LoadResources()
{
	shared_ptr<BGM> MyBGM = make_shared<BGM>
	(
		"DadnMe",
		"../Resources/Audio/BGM/power_up.mp3",
		FMOD_LOOP_NORMAL
	);
	RESOURCE.AddResource(MyBGM);
	AUDIO.AddBGM(MyBGM);
}

void InGame::CreateRenderProperties()
{

}

void InGame::CreateSceneContext()
{
	// Set clear color
	RENDER.SetClearColor({ 0.61f, 0.81f, 0.83f, 1.0f });

	// Set render properties
	CreateRenderProperties();

	// Load nessesary resources
	LoadResources();

#pragma region SCENE_CONTEXT

	// Play bgm
	AUDIO.PlayBGM("DadnMe");

#pragma endregion
}


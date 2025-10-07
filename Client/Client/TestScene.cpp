#include "pch.h"
#include "TestScene.h"

TestScene::TestScene(const string& name) : Super(name)
{

}

void TestScene::CreateSceneContext()
{
#pragma region PREPROCESSING
	RENDER.SetClearColor({ 0.f, 0.0f, 0.2f, 1.0f });
#pragma endregion
}

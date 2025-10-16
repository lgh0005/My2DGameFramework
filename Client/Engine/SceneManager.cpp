#include "pch.h"
#include "SceneManager.h"
#include "Scene.h"

void SceneManager::Init()
{

}

void SceneManager::Update()
{
	_currentScene->Update();
}

void SceneManager::LateUpdate()
{
	if (_currentScene) _currentScene->LateUpdate();
}

void SceneManager::AddScenes(const vector<shared_ptr<Scene>>& scenes)
{
	for (auto& scene : scenes) _scenes[scene->GetName()] = scene;
}

void SceneManager::LoadScene(const string& scene)
{
	if (_currentScene) _currentScene->ClearPreviousSceneContext();

	auto nextScene = _scenes[scene];
	LOGGER.DebugAssert(nextScene == nullptr, format("Failed to load scene. {}", scene), nullptr);

	_currentScene = nextScene;
	_currentScene->Init();
}

void SceneManager::Clear()
{
	if (_currentScene) _currentScene->ClearPreviousSceneContext();
	_currentScene = nullptr;
	_scenes.clear();
}
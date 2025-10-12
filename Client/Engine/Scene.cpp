#include "pch.h"
#include "Scene.h"
#include "IResource.h"
#include "GameObject.h"

Scene::Scene(const string& name) : _name(name)
{

}

void Scene::Init()
{
	// Load scene objects
	CreateSceneContext();

	// Init all game objects
	for (auto& obj : _gameObjects) { obj->Init(); }
}

void Scene::Update()
{
	// Update all game objects
	for (auto& obj : _gameObjects) { obj->FixedUpdate(); }
	for (auto& obj : _gameObjects) { obj->Update(); }
	for (auto& obj : _gameObjects) { obj->LateUpdate(); }
}

void Scene::ClearPreviousSceneContext()
{
	_gameObjects.clear();
	AUDIO.Clear();
	RENDER.Clear();
	RESOURCE.Clear();
}

shared_ptr<GameObject> Scene::GetGameObject(const string& name)
{
	for (auto obj : _gameObjects)
	{
		if (obj->GetName() == name)
			return obj;
	}
	return nullptr;
}

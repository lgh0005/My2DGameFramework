#include "pch.h"
#include "Scene.h"
#include "GameObject.h"

Scene::Scene(const string& name) : _name(name)
{

}

Scene::~Scene()
{

}

void Scene::Init()
{
	// Load scene objects
	CreateSceneContext();

	// Init all game objects
	for (auto& obj : _gameObjects)
		obj->Init();
}

void Scene::Update()
{
	// Update all game objects
	for (auto& obj : _gameObjects)
	{
		obj->FixedUpdate();
		obj->Update();
		obj->LateUpdate();
	}
}

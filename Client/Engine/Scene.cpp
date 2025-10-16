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

void Scene::LateUpdate()
{
	for (auto& obj : _pendingAdd)
	{
		_gameObjects.push_back(obj);
		obj->Init();
	}
	_pendingAdd.clear();

	_gameObjects.erase
	(
		remove_if(_gameObjects.begin(), _gameObjects.end(),
			[](const shared_ptr<GameObject>& obj) { return obj->IsPendingDestroy(); }),
		_gameObjects.end()
	);
}

void Scene::ClearPreviousSceneContext()
{
	_pendingAdd.clear();
	_gameObjects.clear();
	COLLIDER.Clear();
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

void Scene::AddGameObject(const shared_ptr<GameObject>& gameObject)
{
	_pendingAdd.push_back(gameObject);
}

void Scene::AddRenderPass(const string& name, const shared_ptr<RenderPass>& renderPass)
{
	if (_renderPasses.count(name)) return;
	_renderPasses[name] = renderPass;
}

shared_ptr<RenderPass> Scene::GetRenderPass(const string& name)
{
	if (_renderPasses.count(name) == false) return nullptr;
	return _renderPasses[name];
}

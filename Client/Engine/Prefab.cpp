#include "pch.h"
#include "Prefab.h"
#include "Scene.h"

Prefab::Prefab(const string& name) : Super(name)
{

}

void Prefab::SetCurrentScene(const shared_ptr<Scene>& scene)
{
	_currentScene = scene;
}
#include "pch.h"
#include "Prefab.h"
#include "Scene.h"

void Prefab::SetRenderPass(const shared_ptr<RenderPass>& renderPass)
{
	_renderPass = renderPass;
}

void Prefab::SetCurrentScene(const shared_ptr<Scene>& scene)
{
	_currentScene = scene;
}
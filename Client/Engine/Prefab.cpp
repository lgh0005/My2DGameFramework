#include "pch.h"
#include "Prefab.h"

void Prefab::SetRenderPass(const shared_ptr<RenderPass>& renderPass)
{
	_renderPass = renderPass;
}

void Prefab::SetCurrentScene(const shared_ptr<Scene>& scene)
{
	_scene = scene;
}

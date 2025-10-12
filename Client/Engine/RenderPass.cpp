#include "pch.h"
#include "GameObject.h"
#include "RenderPass.h"
#include "Shader.h"
#include "Camera.h"
#include "IRenderable.h"

void RenderPass::Render()
{
	_shader->Use();

	if (_customUniforms) _customUniforms->Apply(_shader);

	for (auto& renderable : _renderables)
	{
		shared_ptr<GameObject> owner;
		if (Utils::IsValidPtr(renderable->GetOwner(), owner) == false) continue;
		if (owner->GetActive() == false) continue;

		renderable->Render(_shader, renderable->GetModel(), _camera);
	}

	_shader->Unuse();
}
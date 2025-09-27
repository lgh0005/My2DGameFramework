#include "pch.h"
#include "RenderPass.h"
#include "Shader.h"
#include "Camera.h"
#include "IRenderable.h"

void RenderPass::Render()
{
	_shader->Use();

	for (auto& renderable : _renderables)
		renderable->Render(_shader, renderable->GetModel(), _camera);

	_shader->Unuse();
}
#include "pch.h"
#include "Prefab.h"

void Prefab::SetRenderPass(const shared_ptr<RenderPass>& renderPass)
{
	_renderPass = renderPass;
}

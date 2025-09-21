#include "pch.h"
#include "UIText.h"

UIText::UIText(const string& name, shared_ptr<Camera> camera, 
	shared_ptr<ITexture> font, shared_ptr<Shader> shader, const glm::vec2& size)
	: Super(name, camera, font, shader, size)
{
}

UIText::~UIText()
{
}

#include "pch.h"
#include "UIText.h"
#include "ITexture.h"

UIText::UIText(const string& name, shared_ptr<ITexture> font, shared_ptr<Shader> shader, const glm::vec2& size)
	: Super(name, font, shader, size)
{
}

UIText::~UIText()
{
}

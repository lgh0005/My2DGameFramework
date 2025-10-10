#include "pch.h"
#include "Texture.h"
#include "UIText.h"

UIText::UIText(const string& name, shared_ptr<Camera> camera, shared_ptr<ITexture> font, const glm::vec2& size)
	: Super(name, camera, font, size)
{

}
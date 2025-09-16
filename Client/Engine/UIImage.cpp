#include "pch.h"
#include "UIImage.h"

UIImage::UIImage(const string& name, shared_ptr<ITexture> image, shared_ptr<Shader> shader, const glm::vec2& size)
	: Super(name, image, shader, size)
{
}

UIImage::~UIImage()
{
}

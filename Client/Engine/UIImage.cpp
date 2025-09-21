#include "pch.h"
#include "UIImage.h"

UIImage::UIImage(const string& name, shared_ptr<Camera> camera, 
	shared_ptr<ITexture> image, shared_ptr<Shader> shader, const glm::vec2& size)
	: Super(name, camera, image, shader, size)
{
}

UIImage::~UIImage()
{
}

#include "pch.h"
#include "Texture.h"
#include "UIImage.h"

UIImage::UIImage(const string& name, shared_ptr<Camera> camera, shared_ptr<ITexture> image, const glm::vec2& size)
	: Super(name, camera, image, size)
{

}

void UIImage::Awake(const shared_ptr<GameObject>& owner)
{
	Super::Awake(owner);
	_texture->Awake();
}

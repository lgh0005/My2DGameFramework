#include "pch.h"
#include "Sprite.h"
#include "ITexture.h"
#include "Texture.h"

Sprite::Sprite(const string& name, shared_ptr<ITexture> texture)
	: Super(name), _texture(texture)
{

}

void Sprite::Render(const shared_ptr<Shader>& shader, const glm::mat4& model, const shared_ptr<Camera>& camera)
{
	_texture->Render(shader, model, camera);
}


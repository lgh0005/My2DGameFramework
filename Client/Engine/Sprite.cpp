#include "pch.h"
#include "Sprite.h"
#include "ITexture.h"
#include "Texture.h"
#include "Shader.h"

Sprite::Sprite(const string& name, shared_ptr<ITexture> texture, shared_ptr<Shader> shader)
	: Super(name), _texture(texture), _shader(shader)
{

}

Sprite::~Sprite()
{

}

void Sprite::Init(shared_ptr<GameObject> owner)
{
	Super::Init(owner);
	_shader->Init();
	_texture->Init();
}

void Sprite::Render()
{
	_texture->Render(_shader, glm::mat4(1.0));
}


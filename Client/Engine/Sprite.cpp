#include "pch.h"
#include "Sprite.h"
#include "ITexture.h"
#include "Texture.h"
#include "Shader.h"
#include "Camera.h"

#pragma region TEST
#include "Transform.h"
#include "GameObject.h"
#pragma endregion

Sprite::Sprite(const string& name, shared_ptr<ITexture> texture, shared_ptr<Shader> shader)
	: Super(name), _texture(texture), _shader(shader)
{

}

Sprite::~Sprite()
{

}

void Sprite::Awake(shared_ptr<GameObject> owner)
{
	Super::Awake(owner);
	_shader->Awake();
	_texture->Awake();
}

void Sprite::Render(const shared_ptr<Camera>& camera)
{
	_texture->Render(_shader, _model, camera);
}


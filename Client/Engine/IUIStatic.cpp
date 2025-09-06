#include "pch.h"
#include "IUIStatic.h"
#include "Texture.h"
#include "Shader.h"
#include "Camera.h"

IUIStatic::IUIStatic(const string& name, shared_ptr<ITexture> texture, shared_ptr<Shader> shader)
	: Super(name, texture->GetSize()), _texture(texture), _shader(shader)
{
}

IUIStatic::~IUIStatic()
{
}

void IUIStatic::Init(shared_ptr<GameObject> owner)
{
	Super::Init(owner);
	_texture->Init();
	_shader->Init();
}

void IUIStatic::Render(const shared_ptr<Camera>& camera)
{
	_texture->Render(_shader, _model, camera);
}

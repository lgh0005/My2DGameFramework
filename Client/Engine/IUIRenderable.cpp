#include "pch.h"
#include "IUIRenderable.h"
#include "ITexture.h"
#include "Shader.h"
#include "Camera.h"
#include "GameObject.h"
#include "Transform.h"

IUIRenderable::IUIRenderable(const string& name, shared_ptr<ITexture> texture, shared_ptr<Shader> shader, const glm::vec2& size)
	: Super(name, size), _texture(texture), _shader(shader)
{
}

IUIRenderable::~IUIRenderable()
{
}

void IUIRenderable::Awake(shared_ptr<GameObject> owner)
{
	Super::Awake(owner);
	_texture->Awake();
	_shader->Awake();
}

void IUIRenderable::Render(const shared_ptr<Camera>& camera)
{
    _texture->Render(_shader, _model, camera);
}
#include "pch.h"
#include "SpriteInstance.h"
#include "ITextureInstance.h"
#include "GameObject.h"
#include "Transform.h"

SpriteInstance::SpriteInstance(const string& name, shared_ptr<ITextureInstance> texture)
	: Super(name), _texture(texture)
{

}

void SpriteInstance::Awake(const shared_ptr<GameObject>& owner)
{
	Super::Awake(owner);
	_texture->Awake();
}

void SpriteInstance::Render(const shared_ptr<Shader>& shader, const glm::mat4& model, const shared_ptr<Camera>& camera)
{
	_texture->Render(shader, model, camera);
}

void SpriteInstance::AddModelMatrix(const glm::mat4& model)
{
	_texture->AddInstance(model);
}

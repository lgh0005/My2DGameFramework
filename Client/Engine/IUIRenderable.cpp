#include "pch.h"
#include "IUIRenderable.h"
#include "ITexture.h"
#include "Camera.h"
#include "GameObject.h"
#include "Transform.h"

IUIRenderable::IUIRenderable(const string& name, const shared_ptr<Camera>& camera, shared_ptr<ITexture> texture, const glm::vec2& size)
	: Super(name, camera, size), _texture(texture)
{

}

void IUIRenderable::Render(const shared_ptr<Shader>& shader, const glm::mat4& model, const shared_ptr<Camera>& camera)
{
	shared_ptr<GameObject> owner;
	if (Utils::IsValidPtr(_owner, owner) == false) return;
	if (owner->IsActive() == false) return;

    _texture->Render(shader, model, camera);
}
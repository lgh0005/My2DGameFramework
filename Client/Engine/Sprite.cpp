#include "pch.h"
#include "GameObject.h"
#include "Transform.h"
#include "Sprite.h"
#include "ITexture.h"
#include "Texture.h"
#include "Camera.h"

Sprite::Sprite(const string& name, shared_ptr<ITexture> texture)
	: Super(name), _texture(texture)
{

}

void Sprite::Render(const shared_ptr<Shader>& shader, const glm::mat4& model, const shared_ptr<Camera>& camera)
{
	shared_ptr<GameObject> owner;
	if (Utils::IsValidPtr(_owner, owner) == false) return;
	if (owner->GetActive() == false) return;

	glm::mat4 renderModel = model;
	if (_parallaxFactor < 1.0f)
	{
		shared_ptr<GameObject> cameraOwner;
		if (Utils::IsValidPtr(camera->GetOwner(), cameraOwner))
		{
			glm::vec3 cameraPos = cameraOwner->GetTransform()->GetPosition();
			renderModel = glm::translate(model, -cameraPos * (1.0f - _parallaxFactor));
		}
	}

	_texture->Render(shader, renderModel, camera);
}


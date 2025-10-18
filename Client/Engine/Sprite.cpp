#include "pch.h"
#include "GameObject.h"
#include "Transform.h"
#include "Shader.h"
#include "Sprite.h"
#include "ITexture.h"
#include "Texture.h"
#include "Camera.h"
#include "IUniformProvider.h"

Sprite::Sprite(const string& name, shared_ptr<ITexture> texture)
	: Super(name), _texture(texture)
{

}

void Sprite::Render(const shared_ptr<Shader>& shader, const glm::mat4& model, const shared_ptr<Camera>& camera)
{
	shared_ptr<GameObject> owner;
	if (Utils::IsValidPtr(_owner, owner) == false) return;
	if (owner->IsActive() == false) return;

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

	// Apply local uniforms
	shared_ptr<IUniformProvider> provider = owner->GetUniformProvider();
	if (provider) provider->ApplyUniforms(shader);

	// Uniforms
	shader->SetUniformValue(Uniforms::UNIFORM_MODEL, model);
	shader->SetUniformValue(Uniforms::UNIFORM_VIEW, camera->GetView());
	shader->SetUniformValue(Uniforms::UNIFORM_PROJECTION, camera->GetProjection());
	shader->SetUniformValue(Uniforms::UNIFORM_TEXTURE, 0);

	// Apply them at once
	shader->ApplyUniforms();

	_texture->Render(shader, renderModel, camera);
}


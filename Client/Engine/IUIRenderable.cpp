#include "pch.h"
#include "IUIRenderable.h"
#include "ITexture.h"
#include "Shader.h"
#include "Camera.h"
#include "GameObject.h"
#include "Transform.h"
#include "IUniformProvider.h"

IUIRenderable::IUIRenderable(const string& name, const shared_ptr<Camera>& camera, shared_ptr<ITexture> texture, const glm::vec2& size)
	: Super(name, camera, size), _texture(texture)
{

}

void IUIRenderable::Render(const shared_ptr<Shader>& shader, const glm::mat4& model, const shared_ptr<Camera>& camera)
{
	shared_ptr<GameObject> owner;
	if (Utils::IsValidPtr(_owner, owner) == false) return;
	if (owner->IsActive() == false) return;

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

    _texture->Render(shader, model, camera);
}
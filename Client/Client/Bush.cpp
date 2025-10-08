#include "pch.h"
#include "Bush.h"

shared_ptr<GameObject> Bush::Instantiate(const string& name, const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale)
{
	auto bush = make_shared<GameObject>(name);
	auto transform = make_shared<Transform>(name, position, rotation, scale);
	bush->SetTransform(transform);

	static auto shader = RESOURCE.GetResource<Shader>("TextureShader");
	static auto texture = RESOURCE.GetResource<Texture>("Bush");

	auto sprite = make_shared<Sprite>(name, texture);
	bush->AddRenderable(static_pointer_cast<IRenderable>(sprite));

	if (_renderPass == nullptr) return nullptr;
	_renderPass->AddRenderable(static_pointer_cast<IRenderable>(sprite));

	return bush;
}

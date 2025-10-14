#include "pch.h"
#include "Building1.h"

shared_ptr<GameObject> Building1::Instantiate(const string& name, const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale)
{
	auto buliding = make_shared<GameObject>(name);
	auto transform = make_shared<Transform>(name, position, rotation, scale);
	buliding->SetTransform(transform);

	static auto shader = RESOURCE.GetResource<Shader>("TextureShader");
	static auto texture = RESOURCE.GetResource<Texture>("Building1");

	auto sprite = make_shared<Sprite>(name, texture);
	buliding->AddRenderable(static_pointer_cast<IRenderable>(sprite));

	if (_renderPass == nullptr) return nullptr;
	_renderPass->AddRenderable(static_pointer_cast<IRenderable>(sprite));

	return buliding;
}

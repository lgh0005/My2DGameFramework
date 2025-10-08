#include "pch.h"
#include "House1.h"

shared_ptr<GameObject> House1::Instantiate(const string& name, const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale)
{
	auto house = make_shared<GameObject>(name);
	auto transform = make_shared<Transform>(name, position, rotation, scale);
	house->SetTransform(transform);

	static auto shader = RESOURCE.GetResource<Shader>("TextureShader");
	static auto texture = RESOURCE.GetResource<Texture>("House1");

	auto sprite = make_shared<Sprite>(name, texture);
	house->AddRenderable(static_pointer_cast<IRenderable>(sprite));

	if (_renderPass == nullptr) return nullptr;
	_renderPass->AddRenderable(static_pointer_cast<IRenderable>(sprite));

	return house;
}

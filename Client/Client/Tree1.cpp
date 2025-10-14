#include "pch.h"
#include "Tree1.h"

shared_ptr<GameObject> Tree1::Instantiate(const string& name, const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale)
{
	auto tree = make_shared<GameObject>(name);
	auto transform = make_shared<Transform>(name, position, rotation, scale);
	tree->SetTransform(transform);

	static auto shader = RESOURCE.GetResource<Shader>("TextureShader");
	static auto texture = RESOURCE.GetResource<Texture>("Tree1");

	auto sprite = make_shared<Sprite>(name, texture);
	sprite->SetParallaxFactor(0.98f);
	tree->AddRenderable(static_pointer_cast<IRenderable>(sprite));

	if (_renderPass == nullptr) return nullptr;
	_renderPass->AddRenderable(static_pointer_cast<IRenderable>(sprite));

	return tree;
}

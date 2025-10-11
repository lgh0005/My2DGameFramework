#include "pch.h"
#include "ColliderDebuger.h"

shared_ptr<GameObject> ColliderDebuger::Instantiate(const string& name, const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale)
{
	auto test = make_shared<GameObject>(name);
	auto transform = make_shared<Transform>(name, position, rotation, scale);
	test->SetTransform(transform);

	static auto shader = RESOURCE.GetResource<Shader>("TextureShader");
	static auto texture = RESOURCE.GetResource<Texture>("TEST");

	auto sprite = make_shared<Sprite>(name, texture);
	test->AddRenderable(static_pointer_cast<IRenderable>(sprite));

	if (_renderPass == nullptr) return nullptr;
	_renderPass->AddRenderable(static_pointer_cast<IRenderable>(sprite));

	return test;
}

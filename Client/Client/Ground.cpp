#include "pch.h"
#include "Ground.h"

shared_ptr<GameObject> Ground::Instantiate(const string& name, const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale)
{
	auto ground = make_shared<GameObject>(name);
	auto transform = make_shared<Transform>(name, position, rotation, scale);
	ground->SetTransform(transform);

	static auto shader = RESOURCE.GetResource<Shader>("TextureShader");
	static auto texture = RESOURCE.GetResource<Texture>("Ground");

	auto sprite = make_shared<Sprite>(name, texture);
	ground->AddRenderable(static_pointer_cast<IRenderable>(sprite));

	auto collider = make_shared<BoxCollider>("GroundCollider", glm::vec2(800.0f, 100.0f));
	COLLIDER.AddColliderComponent(collider);
	ground->AddComponent(collider);

	if (_renderPass == nullptr) return nullptr;
	_renderPass->AddRenderable(static_pointer_cast<IRenderable>(sprite));

	return ground;
}

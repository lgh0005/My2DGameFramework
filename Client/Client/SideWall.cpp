#include "pch.h"
#include "SideWall.h"

shared_ptr<GameObject> SideWall::Instantiate(const string& name, const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale)
{
	auto background = make_shared<GameObject>(name);
	auto transform = make_shared<Transform>(name, position, rotation, scale);
	background->SetTransform(transform);

	static auto shader = RESOURCE.GetResource<Shader>("TextureShader");
	static auto texture = RESOURCE.GetResource<Texture>("SideWall");

	auto sprite = make_shared<Sprite>(name, texture);
	background->AddRenderable(static_pointer_cast<IRenderable>(sprite));

	auto collider = make_shared<BoxCollider>("WallCollider", glm::vec2(100.0f, 800.0f));
	COLLIDER.AddColliderComponent(collider);
	background->AddComponent(collider);

	if (_renderPass == nullptr) return nullptr;
	_renderPass->AddRenderable(static_pointer_cast<IRenderable>(sprite));

	return background;
}
